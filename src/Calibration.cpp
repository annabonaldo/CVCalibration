#include "Calibration.h"
#include <iostream>
#include "Datasets.h"

using namespace std; using namespace cv; bool Calibration::show_each_findChessboardCorners_result = true;std::vector<std::vector<cv::Point3f>> Calibration::objectPoints = std::vector<std::vector<Point3f>>();std::vector<std::vector<cv::Point2f>> Calibration::imagePoints = std::vector<std::vector<Point2f>>();std::map<double, std::list<std::string>> Calibration::errorMap = std::map<double, std::list<std::string>>(); std::vector<string> Calibration::input_images_files = std::vector<string>();cv::Mat Calibration::cameraMatrix = cv::Mat(); 
cv::Mat Calibration::distCoeffs = cv::Mat();
cv::Mat Calibration::map1 = cv::Mat();
cv::Mat Calibration::map2 = cv::Mat();

Calibration::Calibration()
{
}

Calibration::~Calibration()
{
}

void Calibration::save(double error, std::string filename) {
	if (errorMap.find(error) != errorMap.end())
		errorMap.at(error).push_back(filename);
	else
	{
		std::list<string> list = std::list<string>();
		list.push_back(filename);
		errorMap.insert(pair<double, std::list<string>>(error, list));
	}

}

void Calibration::save(double calibration, double reproj, std::string file)
{

	FileStorage fs(file, FileStorage::WRITE);
	fs << "intrinsic" << cameraMatrix;
	fs << "distCoeffs" << distCoeffs;
	fs << "Mean reprojection error" << reproj;

	for (std::map<double, list<string>>::iterator it = errorMap.begin(); it != errorMap.end(); it++)
		for (std::list<string>::iterator fileit = it->second.begin(); fileit != it->second.end(); fileit++)
			fs << "file error" << "file name: " + (*fileit) + " - error: " + to_string(it->first);
	
}

void Calibration::clear()
{
	objectPoints = std::vector<std::vector<Point3f>>();	imagePoints = std::vector<std::vector<Point2f>>();	errorMap = std::map<double, std::list<std::string>>();	input_images_files = std::vector<string>();	cameraMatrix = Mat();
	distCoeffs = Mat();
	map1 = Mat();
	map2 = Mat();
}

std::vector<std::string> Calibration::getBestN(int i)
{
	std::vector<std::string> bestFiles = std::vector<std::string>(); 
	if (!errorMap.empty())
	{
		for (std::map<double, list<string>>::iterator it = errorMap.begin(); it != errorMap.end() && (i > 0); it++)
			for (std::list<string>::iterator fileit = it->second.begin();
				fileit != it->second.end() && (i > 0); i--, fileit++)
				bestFiles.push_back(*fileit); 
	}
	return bestFiles; 
}

void Calibration::datasetCalibration(vector<string> input_images_files, string datasetName, string experimentName)
{
	Datasets::logDatasetStart(datasetName); 
	clear(); 
	cv::Mat img, img2;
	Size imageSize;
	vector<Point2f> imageCorners;
	vector<Point3f> objectCorners;

	int numCornersHor =  Datasets::datasets[datasetName].H_squares;
	int numCornersVer =  Datasets::datasets[datasetName].V_squares;
	double square_size = Datasets::datasets[datasetName].square_size;
	
	int numSquares = numCornersHor * numCornersVer;
	cv::Size boardSize(numCornersHor, numCornersVer);

	std::cout << "Dataset settings:: Number chessboard's horizontal corners: " << numCornersHor << std::endl;
	std::cout << "Dataset settings:: Number chessboard's vertical corners: " << numCornersVer << std::endl;
	std::cout << "Dataset settings:: Chessboard's square size: " << square_size << std::endl << std::endl;

	for (int i = 0; i < boardSize.height; i++)	
		for (int j = 0; j < boardSize.width; j++)
			objectCorners.push_back(Point3f(i*square_size, j*square_size, 0));
	
	std::cout << "Calibaration process:: Finding chessboard corners for each input file... " << std::endl;


	for (int f = 0; f < input_images_files.size(); f++)
	{
		string filename = input_images_files[f];
		img = imread(filename, 0);
		std::cout << "*                     --> processing img " << filename << std::endl; 
		if (img.empty()) std::cout << "*                     --> WARNING: empty image file " << filename << std::endl;
		else
		{
			// Find chessboard corners 
			bool found = cv::findChessboardCorners(img, boardSize, imageCorners);
			if (found) // Find exact val of corners 
			{	
				cornerSubPix(img, imageCorners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1));
				if (imageCorners.size() == boardSize.area())
				{
					imagePoints.push_back(imageCorners);
					objectPoints.push_back(objectCorners);
				}

				img.copyTo(img2);

				//Draw chessboard corners
				cv::drawChessboardCorners(img2, boardSize, imageCorners, found);
				//************************
				cv::Size imgSize = img2.size();
				if (show_each_findChessboardCorners_result)
				{
					namedWindow("image", WINDOW_NORMAL);
					resizeWindow("image",640,480); 
					imshow("image", img2);
					waitKey(0);
				}
			}
		}
	}
	cvDestroyAllWindows();
	if (show_each_findChessboardCorners_result) cvDestroyWindow("image");

	vector<Mat> rvecs, tvecs;
	std::cout << "Calibration process:: Waiting for calibration process... " << std::endl;

	double error = calibrateCamera(objectPoints, imagePoints, img.size(), cameraMatrix, distCoeffs, rvecs, tvecs);
	
	vector<float> perViewErrors = vector<float>();
	double rerror = getReprojectionErrors(rvecs, tvecs, perViewErrors);
	
	std::cout << "Calibration process:: calibration completed; " << std::endl;
	std::cout << "Calibration process:: CALIBRATION ERRORS :  " << std::endl;
	std::cout << "*                     ---> Mean repjection error: " << rerror << std::endl;	
	
	for (int r = 0; r < perViewErrors.size(); r++)
	{
		std::cout << "*                     ------> error for image " << r << ": " << perViewErrors[r] << std::endl;
		save(perViewErrors[r], input_images_files[r]);
	}
	save(error, rerror, "..\\results\\"+ experimentName+".yml");


	Mat map1, map2; // undistort map1, 2 
	Mat testimg = imread(Datasets::datasets[datasetName].test, 0);
	Mat utestimg;
	

	cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix, img.size(), CV_32FC1, map1, map2);
	cv::remap(testimg, utestimg, map1, map2, INTER_LINEAR);
	cv::undistort(testimg, utestimg, cameraMatrix, distCoeffs, Mat());


	Mat win_mat;
	hconcat(testimg, utestimg, win_mat);
	
	// Display split view
	namedWindow("Remapped image", WINDOW_NORMAL);
	resizeWindow("Remapped image", 1240, 480);
	cv::imshow("Remapped image", win_mat);

	waitKey(0);
	cvDestroyAllWindows();
	Datasets::logDatasetEnd(datasetName);
}

double Calibration::getReprojectionErrors(
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	vector<float>& perViewErrors)
{
	vector<Point2f> imagePoints2;
	size_t totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());
	for (size_t i = 0; i < objectPoints.size(); ++i)
	{
		
		projectPoints(objectPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
		
		err = norm(imagePoints[i], imagePoints2, NORM_L2);
		size_t n = objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err / n);
		totalErr += err*err;
		totalPoints += n;
	}
	return std::sqrt(totalErr / totalPoints);
}


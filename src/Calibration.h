#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>
#include <opencv2/calib3d.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std; 
using namespace cv; 
class Calibration 
{
public:
	Calibration();
	~Calibration();
	static void clear(); 
	static bool show_each_findChessboardCorners_result;

	static double getReprojectionErrors(
		const std::vector<Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
		std::vector<float>& perViewErrors); 

	static void datasetCalibration(std::vector<std::string> input_images_files, std::string datsetName, std::string experimentnName);
	static void save(double error, std::string filename);
	static void save(double clibrationErr, double rpjErr, std::string file);
	static std::vector<std::string> getBestN(int i); 

private: 
	static std::vector<std::vector<cv::Point3f>> objectPoints;	static std::vector<std::vector<cv::Point2f>> imagePoints;	static std::map<double, std::list<std::string>> errorMap;	static std::vector<std::string> input_images_files;		static cv::Mat cameraMatrix;
	static cv::Mat distCoeffs;
	static cv::Mat map1, map2;

	
};


#include <iostream>
#include "Calibration.h"
#include "Datasets.h"

using namespace cv; 
int main(int argc, char** argv) {

	// IF THIS VALUE IS SET TO TRUE 
	// ALL DATASET IMAGES WILL BE SHOWN WITH CHESSBOARD CORNERS FOUND DURING CALIBRATION INTERMEDIATE PROCESS

	// if VALUE == TRUE  YOU MUST PRESS ENTER AFTER EACH IMAGE DIPLAY TO GO ON IN CALIBRATION FUNCTION
	// Don't set it to true on large datasets!!
	Calibration::show_each_findChessboardCorners_result = false;

	// set all dataset files path into Databases obj
	Datasets::load();

	std::vector<std::string> data5 = std::vector<std::string>();
	std::vector<std::string> data10 = std::vector<std::string>();
	std::vector<std::string> data20 = std::vector<std::string>();

	// Perform calibration process on dataset 1
	Calibration::datasetCalibration(Datasets::datasets[Datasets::dataset1].input_files, Datasets::dataset1, "dataset1"/*experiment name*/);

	////// Repeats calibration process using best N imgases 
	////// Data on best N images are collected from previous full dataset calibration 
	/***/ data5 = Calibration::getBestN(5);
	/***/ data10 = Calibration::getBestN(10);
	/***/ data20 = Calibration::getBestN(20);
	/***/
	/***/ Calibration::datasetCalibration(data5, Datasets::dataset1, "dataset1_best5"/*experiment name*/);
	/***/ Calibration::datasetCalibration(data10, Datasets::dataset1, "dataset1_best10"/*experiment name*/);
	/***/ Calibration::datasetCalibration(data20, Datasets::dataset1, "dataset1_best20"/*experiment name*/);

	// !!! DISABLED DATASET2
	// Move dataset4 into data folder and before setting activeDataset2 = true; 
	bool activeDataset2 = false;
	if (activeDataset2) // Dataset 2 is disabled
	{

		// Perform calibration process on dataset 2
		Calibration::datasetCalibration(Datasets::datasets[Datasets::dataset2].input_files, Datasets::dataset2, "dataset2"/*experiment name*/);
	}

	// !!! DISABLED DATASET3
	// Move dataset4 into data folder and before setting activeDataset4 = true; 
	bool activeDataset3 = false;
	if (activeDataset3) // Dataset 3 is disabled
	{
		// Perform calibration process on dataset 3
		Calibration::datasetCalibration(Datasets::datasets[Datasets::dataset3].input_files, Datasets::dataset3, "dataset3"/*experiment name*/);
	}
	
	// !!! DISABLED DATASET4
	// Move dataset4 into data folder and before setting activeDataset4 = true; 
	bool activeDataset4 = false; 
	if (activeDataset4) // Dataset 4 is disabled
	{
		// Perform calibration process on dataset 4
		Calibration::datasetCalibration(Datasets::datasets[Datasets::dataset4].input_files, Datasets::dataset4, "dataset4"/*experiment name*/);

		data5.clear();
		data10.clear();
		////// Repeats calibration process using best N imgases 
		////// Data on best N images are collected from previous full dataset calibration 
		/***/  data5 = Calibration::getBestN(5);
		/***/  data10 = Calibration::getBestN(10);
		/***/  Calibration::datasetCalibration(data5, Datasets::dataset4, "dataset4_best5"/*experiment name*/);
		/***/  Calibration::datasetCalibration(data10, Datasets::dataset4, "dataset4_best10"/*experiment name*/);
	}

	// output result are in .yml format into the result folder: 
	//           result\esperiment_name.yml  

	cin.ignore();

	return 0;
}


// ComputerVision.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Examples.h"
#include "Lab01.h"
#include "Lab02.h"
#include "Lab03.h"
#include "Calibration.h"
#include "Datasets.h"
#include <iostream>
using namespace cv; 

int main(int argc, char** argv) {

	Calibration::show_each_findChessboardCorners_result = false; 

	Calibration lab = Calibration();
	Datasets::load(); 
	std::vector<std::string> data5 = std::vector<std::string>(); 
	std::vector<std::string> data10 = std::vector<std::string>();
	std::vector<std::string> data20 = std::vector<std::string>();

	lab.datasetCalibration(Datasets::datasets[Datasets::dataset1].second, Datasets::dataset1, "dataset1"); 

	data5 = Calibration::getBestN(5); 
	data10 = Calibration::getBestN(10);
	data20 = Calibration::getBestN(20);

	lab.datasetCalibration(data5, Datasets::dataset1, "dataset1_best5");
	lab.datasetCalibration(data10, Datasets::dataset1, "dataset1_best10");
	lab.datasetCalibration(data20, Datasets::dataset1, "dataset1_best20");

	lab.datasetCalibration(Datasets::datasets[Datasets::dataset2].second, Datasets::dataset2, "dataset2");

	return 0;
}

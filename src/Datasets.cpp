
#include "Datasets.h"
#include "string"
#include <map>
#include <iostream>
using namespace std; 
std::string Datasets::dataset1 = "dataset1";
std::string Datasets::dataset2 = "dataset2";
std::string Datasets::dataset3 = "dataset3";
std::string Datasets::dataset4 = "dataset4";

std::map<std::string, Datasets::settings> Datasets::datasets =
	std::map < std::string, Datasets::settings>(); 

void Datasets::load()
{
	settings set1 = settings(1.0,5, 6, "..\\data\\dataset1\\test.png");

	datasets.insert(std::pair<string,settings>(dataset1, set1) );
	int i = 1; 
	for (; i < 10; i++)
		datasets[dataset1].input_files.push_back("..\\data\\" + dataset1 + "\\" + "000" + to_string(i) + "_color.png");
	for (; i < 59; i++)
		datasets[dataset1].input_files.push_back("..\\data\\" + dataset1 + "\\" + "00" + to_string(i) + "_color.png");


	settings set2 = settings(1.0, 7, 6, "..\\data\\dataset2\\test.jpg");

	datasets.insert(std::pair<string, settings>(dataset2, set2));


	for (int i=101; i < 113; i++)
		datasets[dataset2].input_files.push_back("..\\data\\" + dataset2 + "\\" + to_string(i) + ".jpg");


	settings set3 = settings(1.0, 7, 6, "..\\data\\dataset3\\test.jpg");
	datasets.insert(std::pair<string, settings>(dataset3, set3));
	for (int i = 101; i < 113; i++)
		datasets[dataset3].input_files.push_back("..\\data\\" + dataset3 + "\\" + to_string(i) + ".jpg");

	settings set4 = settings(0.19, 12, 8, "..\\data\\dataset4\\test.JPG");
	datasets.insert(std::pair<string, settings>(dataset4, set4));
	for (int i = 101; i < 122; i++)
		datasets[dataset4].input_files.push_back("..\\data\\" + dataset4 + "\\" + to_string(i) + ".JPG");


}
void Datasets::logDatasetStart(std::string dataset) {

	std::cout << " ********************************************************************************* " << std::endl 
			  << "  CALIBRATION ON DATSET: "+ dataset << std::endl
			  << " ********************************************************************************* " << std::endl 
		     << std::endl;
}

void Datasets::logDatasetEnd(std::string dataset) {

	std::cout 
		<< " ********************************************************************************* " << std::endl
		<< "   END DATASET CALIBRATION ON : " + dataset << std::endl
		<< " ********************************************************************************* " << std::endl
		<< std::endl;
}
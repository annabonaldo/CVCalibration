#pragma once
#include <map>
#include <vector>
class Datasets
{
public:
	struct settings
	{
	public:
		double square_size; 
		int H_squares; 
		int V_squares; 
		std::string test; 
		std::vector<std::string> input_files; 
		settings(){}
		settings(double s, int H, int V, std::string t, std::vector<std::string> f = std::vector<std::string>()) :
			square_size(s), H_squares(H), V_squares(V), test(t), input_files(f) {}
	};

	static std::map<std::string, settings> datasets; 
	static void load(); 
	static std::string dataset1; 
	static std::string dataset2; 
	static std::string dataset3;
	static std::string dataset4;

	static void logDatasetStart(std::string dataset);
	static void logDatasetEnd(std::string dataset);


};


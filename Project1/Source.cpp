#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

int main()
{
	std::vector<std::string> ideasVec;

	std::fstream infile;
	infile.open("ideas.txt");
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		ideasVec.push_back(line);
	}


	system("pause");
}
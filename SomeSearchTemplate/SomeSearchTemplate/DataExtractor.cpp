#include "stdafx.h"
#include "DataExtractor.h"

#include <fstream>

using namespace std;

TemplateSearchData DataExtractor::extractData(const std::string fileName)
{
	size_t templateAmount = 0;
	std::vector<std::string> templates = std::vector<std::string>();
	string inputFileName;

	ifstream inputFile(fileName);
	bool inputFileIsOpen = inputFile.is_open();

	if (inputFileIsOpen)
	{
		inputFile >> templateAmount;

		string inputString;
		if (!inputFile.eof())
		{
			getline(inputFile, inputString);
		}
		while (!inputFile.eof())
		{
			getline(inputFile, inputString);
			templates.push_back(inputString);
		}
	}
	else {
		throw new std::exception(std::string("\"" + fileName + "\" not opened").c_str());
	}
		
	inputFileName = templates[templates.size() - 1];
	templates.pop_back();

	return TemplateSearchData(templateAmount, templates, inputFileName);
}

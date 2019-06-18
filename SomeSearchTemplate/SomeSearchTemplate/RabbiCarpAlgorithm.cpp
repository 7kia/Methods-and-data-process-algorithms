#include "stdafx.h"
#include "RabbiCarpAlgorithm.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <cctype>

using namespace std;


vector<vector<FoundPositions>> RabbiCarpAlgorithm::foundTemplates(const TemplateSearchData data)
{
	vector<vector<FoundPositions>> foundTemplates = vector<vector<FoundPositions>>();

	ifstream inputFile(data.fileName);
	bool inputFileIsOpen = inputFile.is_open();

	if (inputFileIsOpen)
	{
		const vector<string> templates = toLowerCase(data.templates);
		const vector<size_t> templateSizes = getTemplateSizes(templates);
		const size_t maxTemplateLength = *std::max_element(templateSizes.begin(), templateSizes.end());
		const vector<Hash> templateHashs = m_hashFunction.getHashs(templates);

		const TemplateData templateData = TemplateData(
			templates,
			templateSizes,
			maxTemplateLength,
			templateHashs
		);

		string inputString;
		while (!inputFile.eof())
		{
			getline(inputFile, inputString);
			size_t secondStringPos = inputFile.tellg();
			const bool foundFirstString = inputString.size() > 0;
			bool foundSecondString = false;
			if (foundFirstString) {
				foundSecondString = foundSecondStringAndHandle(
					inputFile,
					inputString, 
					templateData, 
					foundTemplates
				);				
			}

			if (!inputFile.eof() || foundSecondString) {
				inputFile.seekg(secondStringPos);
			}
		}
	}
	else {
		throw new std::exception((std::string("\"" + data.fileName + "\" not opened").c_str()));
	}

	return foundTemplates;
}

std::vector<size_t> RabbiCarpAlgorithm::getTemplateSizes(const std::vector<std::string>& templates)
{
	std::vector<size_t> result;
	for each (string temp in templates)
	{
		result.push_back(temp.size());
	}
	return result;
}

void RabbiCarpAlgorithm::handleString(
	const std::string& inputString, 
	vector<vector<FoundPositions>>& foundTemplates,
	const TemplateData& templateData,
	const size_t endCompareIndex
)
{
	string lowerCaseString = toLowerCase(inputString);
	std::transform(inputString.begin(), inputString.end(), lowerCaseString.begin(), ::tolower);
	vector<FoundPositions> positions = m_hashFunction.compare(
		templateData.templateHashs,
		templateData.templateSizes,
		templateData.maxTemplateLength,
		lowerCaseString,
		endCompareIndex
	);
	foundTemplates.push_back(positions);
}

bool RabbiCarpAlgorithm::foundSecondStringAndHandle(
	ifstream &inputFile, 
	const string& string1,
	const TemplateData& templateData,
	vector<vector<FoundPositions>>& result
)
{
	const bool existSecondString = !inputFile.eof();
	if (existSecondString)
	{
		string inputString;
		getline(inputFile, inputString);
		handleString(
			string1 + " " + inputString.substr(0, templateData.maxTemplateLength - 1),
			result,
			templateData,
			string1.size()
		);
		return true;
	}
	else
	{
		handleString(string1, result, templateData, string1.size());
		return false;
	}
}

std::vector<std::string> RabbiCarpAlgorithm::toLowerCase(const std::vector<std::string> templates)
{
	std::vector<std::string> result = templates;

	for (size_t i = 0; i < templates.size(); ++i)
	{
		result[i] = toLowerCase(templates[i]);
	}

	return result;
}

char change_case(unsigned char c) {
	if (c > 192 && c < 255) {
		return tolower(c);
	}
	return c;
}

std::string RabbiCarpAlgorithm::toLowerCase(const std::string string)
{
	//std::locale loc;
	std::string result = std::string(string);
	//for (std::string::size_type i = 0; i < string.length(); ++i) {
	//	result += std::tolower(string[i]);
	//}
	std::transform(string.begin(), string.end(), result.begin(), change_case);

	return result;
}


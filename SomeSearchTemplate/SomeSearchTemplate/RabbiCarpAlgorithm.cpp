#include "stdafx.h"
#include "RabbiCarpAlgorithm.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cmath>

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

		vector<Hash> templateHashs = m_hashFunction.getHashs(templates);

		string inputString;
		std::locale loc;
		while (!inputFile.eof())
		{
			getline(inputFile, inputString);

			std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
			vector<FoundPositions> positions = m_hashFunction.compare(
				templateHashs, 
				templateSizes,
				maxTemplateLength, 
				inputString
			);
			foundTemplates.push_back(positions);
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

std::vector<std::string> RabbiCarpAlgorithm::toLowerCase(const std::vector<std::string> templates)

{
	std::vector<std::string> result = std::vector<std::string>(templates.size() - 1);

	for (size_t i = 0; i < templates.size(); ++i)
	{
		std::transform(templates[i].begin(), templates[i].end(), result[i].begin(), ::tolower);
	}

	return result;
}

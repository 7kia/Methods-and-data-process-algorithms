// SomeSearchTemplate.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <locale>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>

#include "DataExtractor.h"
#include "AhoKorasikAlgorithm.h"
#include "RabbiCarpAlgorithm.h"

using namespace std;

void compareFiles(const string firstFileName, const string secondFileName)
{
	ifstream firstFile(firstFileName);
	ifstream secondFile(secondFileName);

	bool firstIsOpen = firstFile.is_open();
	bool secondIsOpen = secondFile.is_open();

	if (firstIsOpen && secondIsOpen)
	{
		cout << "Compare files ";
		cout << firstFileName.c_str();
		cout << " and ";
		cout << secondFileName.c_str() << endl;

		string str1;
		string str2;
		bool result = true;
		size_t stringCounter = 1;
		while (!firstFile.eof() && !secondFile.eof())
		{
			getline(firstFile, str1);
			getline(secondFile, str2);
			if (str1.compare(str2) != 0)
			{
				result = false;
				cout << "Not equal "; cout << stringCounter; cout << " string" << endl;
				cout << "First: "; cout << str1.c_str() << endl;
				cout << "Second: "; cout << str2.c_str() << endl;
				cout << endl;
			}
			++stringCounter;
		}
		if (result) {
			string msg = "Files " + firstFileName + " and " + secondFileName + " equal";
			cout << msg.c_str() << endl;
		}
		cout << endl;
			
	}
	else {
		if (!firstIsOpen) {
			throw new std::exception((std::string("\"" + firstFileName + "\" not opened").c_str()));
		}
		if(!secondIsOpen)
		{
			throw new std::exception((std::string("\"" + secondFileName + "\" not opened").c_str()));
		}
	}
		
}

void recordResult(
	const std::vector<std::vector<FoundPositions>>& result, 
	const string outputFileName,
	const vector<string> templates
) {
	fstream outputFile(outputFileName);

	bool isOpen = outputFile.is_open();

	if (isOpen)
	{
		size_t stringCount = 1;
		std::stringstream stream;

		for (size_t stringCount = 0; stringCount < result.size(); ++stringCount)
		{
			stream.clear();

			const vector<FoundPositions>& lineResult = result[stringCount];
			for (size_t i = 0; i < lineResult.size(); ++i)
			{
				const FoundPositions& templatePositions = lineResult[i];

				for (size_t tempIndex = 0; tempIndex < lineResult.size(); ++tempIndex)
				{
					const size_t position = templatePositions[tempIndex];
					stream << "Line " << stringCount << ": position " << position << ": " << templates[tempIndex] << "\n";
					outputFile << stream;// TODO: 
				}


			}

		}
	}
	else
	{			
		throw new std::exception((std::string("\"" + outputFileName + "\" not opened").c_str()));
	}
}

void testAlgorithms(const string inputFileName, const string outputFileName)
{
	DataExtractor dataExtractor = DataExtractor();
	TemplateSearchData data = dataExtractor.extractData(inputFileName + ".txt");
	
	auto func = [=](IStringTemplateSearcher& algorithm, const string algorithmName) {
		try
		{
			cout << "Work " << algorithmName << "; File \"" << inputFileName << "\"" << endl;

			std::clock_t start;
			double duration;
			start = std::clock();

			std::vector<std::vector<FoundPositions>> result = algorithm.foundTemplates(data);

			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			std::cout << "time=" << duration << '\n';


			compareFiles(data.fileName, outputFileName + "_" + algorithmName + ".txt");
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}
	};

	func(RabbiCarpAlgorithm(), "Rabbi-Carp");
	func(AhoKorasikAlgorithm(), "Aho-Korasik");
}

int main()
{
	testAlgorithms("input", "output");

	// Test compareFiles()
	//compareFiles("output_r.txt", "output__r.txt");
	//compareFiles("output_.txt", "output__1.txt");
    return 0;
}


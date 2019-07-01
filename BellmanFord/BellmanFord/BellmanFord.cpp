// BellmanFord.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "DataExtractor.h"
#include "BellmanFordAlgorithm.h"

#include <string>
#include <locale>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <functional>
#include <vector>

using namespace std;

void compareFiles(const string firstFileName, const string secondFileName, const bool logging)
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
				if (logging) {
					cout << "Not equal "; cout << stringCounter; cout << " string" << endl;
					cout << "First: "; cout << str1.c_str() << endl;
					cout << "Second: "; cout << str2.c_str() << endl;
					cout << endl;
				}
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
		if (!secondIsOpen)
		{
			throw new std::exception((std::string("\"" + secondFileName + "\" not opened").c_str()));
		}
	}

}


void recordStrings(
	fstream& outputFile
) {

	//for (size_t stringCount = 0; stringCount < result.size(); ++stringCount)
	//{


	//	const vector<FoundPositions>& lineResult = result[stringCount];
	//	for (size_t i = 0; i < lineResult.size(); ++i)
	//	{
	//		const FoundPositions& templatePositions = lineResult[i];

	//		for (size_t tempIndex = 0; tempIndex < templatePositions.size(); ++tempIndex)
	//		{
	//			std::stringstream stream;

	//			const size_t position = templatePositions[tempIndex];
	//			stream << "Line " << stringCount + 1 << ": position " << position + 1 << ": " << templates[i] << "\n";
	//			outputFile << stream.str();// TODO: 
	//		}


	//	}

	//}
}

void foo()
{
	throw new exception("1");
}

void recordbeautifulString(const MaxPathData& data, fstream& outputFile)
{
	if (data.length)
	{
		outputFile << "Path length =" << data.length << "; Path vertex amount =" << data.path.size() << ";\n";
	}
	else
	{
		outputFile << "Path from " << data.from << " to " << data.to << "not exist";
	}
}

void recordString(const MaxPathData& data, fstream& outputFile, const bool beautifulOutput)
{
	BellmanFordAlgorithm algorithm = BellmanFordAlgorithm();
	outputFile << algorithm.printPath(data, beautifulOutput);
}

void recordResult(
	const vector<MaxPathData>& result,
	const string outputFileName,
	const bool beautifulOutput
) {
	fstream outputFile(outputFileName);

	bool isOpen = outputFile.is_open();

	if (isOpen)
	{
		for (size_t i = 0; i < result.size(); ++i)
		{
			recordString(result[i], outputFile, beautifulOutput);
		}		
	}
	else
	{
		throw new std::exception((std::string("\"" + outputFileName + "\" not opened").c_str()));
	}
}

void executeAndMeasureTime(std::function<void()> function) {
	std::clock_t start;
	double duration;
	start = std::clock();

	function();

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "time=" << duration << '\n';
}

void testAlgorithms(
	const string inputFileName,
	const string outputFileName,
	const bool logging,
	const bool beautifulOutput
)
{
	DataExtractor dataExtractor = DataExtractor();
	GraphData data = dataExtractor.extractDataFrom(inputFileName + ".txt");

	try
	{
		cout << "File \"" << inputFileName << "\"" << endl;

		vector<MaxPathData> result;
		executeAndMeasureTime([&]()
		{
			BellmanFordAlgorithm algorithm = BellmanFordAlgorithm();
			result = algorithm.getMaxPaths(data.graph);
		});

		recordResult(result, outputFileName + ".txt", beautifulOutput);
		compareFiles(inputFileName + ".txt", outputFileName + ".txt", logging);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");
	testAlgorithms("input1", "output1", true, true);
	testAlgorithms("input2", "output2", true, true);
	// testAlgorithms("input2", "output2", false);
	// Test compareFiles()
	//compareFiles("output_r.txt", "output__r.txt");
	//compareFiles("output_.txt", "output__1.txt");
	return 0;
}


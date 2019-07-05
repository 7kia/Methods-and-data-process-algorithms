// BellmanFord.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "DataExtractor.h"
#include "BellmanFordAlgorithm.h"
#include "MaxPathPrinter.h"

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
	MaxPathPrinter printer = MaxPathPrinter();
	outputFile << printer.printPath(data, beautifulOutput);
}

void recordResult(
	const std::vector<MaxPathData>& result,
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
	try
	{
		DataExtractor dataExtractor = DataExtractor();
		const GraphData data = dataExtractor.extractDataFrom(inputFileName + ".txt");



		cout << "File \"" << inputFileName << "\"" << endl;

		BellmanFordAlgorithm::MaxPaths result;
		executeAndMeasureTime([&]()
		{
			BellmanFordAlgorithm algorithm = BellmanFordAlgorithm();
			result = algorithm.getMaxPaths(data.graph, data.startVertex);
		});

		recordResult(result, outputFileName + ".txt", beautifulOutput);
		//compareFiles(outputFileName + ".txt", outputFileName + "_r.txt", logging);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");

	//testAlgorithms("input1", "output1", true, true);
	//testAlgorithms("input2", "output2", true, true);
	//testAlgorithms("input3", "output3", true, true);
	testAlgorithms("input4", "output4", true, true);
	testAlgorithms("input5", "output5", false, true);//0.354
	testAlgorithms("input6", "output6", false, true);//3.905
	testAlgorithms("input9", "output9", false, true);//6.918 vs 4
	testAlgorithms("input13", "output13", false, true);//25.914 vs 14

	//testAlgorithms("input12", "output12", true, true);
	//testAlgorithms("input13", "output13", true, true);
	// testAlgorithms("input2", "output2", false);
	// Test compareFiles()
	//compareFiles("output_r.txt", "output__r.txt");
	//compareFiles("output_.txt", "output__1.txt");
	return 0;
}


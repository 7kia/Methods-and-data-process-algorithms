// DijkstraAndBinaryHeap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"

#include "MyGraph.h"

#include <locale>
#include <fstream>
#include <ctime>
#include <cstdio>

using namespace std;

void testFile(const string inputFileName, const string outputFileName) {
	std::clock_t start;
	double duration;
	start = std::clock();

	Dijkstra algorithm = Dijkstra();
	const string output = algorithm.findMinPath(inputFileName);
	ofstream outputFile;
	outputFile.open(outputFileName);
	outputFile << output;
	outputFile.close();

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "File \"" << inputFileName <<"\" time=" << duration << '\n';
}

int main() {
	setlocale(LC_ALL, "Russian");
	const size_t SIZE = 6;

	testFile("input.txt", "output.txt");
	testFile("input2.txt", "output2.txt");
	testFile("inputReverse.txt", "outputReverse.txt");
	testFile("input_From_1_to_5.txt", "output_From_1_to_5.txt");
	testFile("input_less_road.txt", "output_less_road.txt");
	testFile("input_more_road.txt", "output_more_road.txt");
	testFile("inputBig.txt", "outputBig.txt");
	return 0;
}


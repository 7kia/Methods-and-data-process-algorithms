// DijkstraAndBinaryHeap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"

#include "MyGraph.h"

#include <locale>
#include <fstream>

using namespace std;

void testFile(const string inputFileName, const string outputFileName) {
	Dijkstra algorithm = Dijkstra();
	const string output = algorithm.findMinPath(inputFileName);
	ofstream outputFile;
	outputFile.open(outputFileName);
	outputFile << output;
	outputFile.close();
}

int main() {
	// Граф взят отсюда https://prog-cpp.ru/deikstra/
	setlocale(LC_ALL, "Russian");
	const size_t SIZE = 6;

	testFile("input.txt", "output.txt");
	testFile("inputReverse.txt", "outputReverse.txt");
	testFile("input_From_1_to_5.txt", "output_From_1_to_5.txt");
	testFile("input_less_road.txt", "output_less_road.txt");
	testFile("input_more_road.txt", "output_more_road.txt");
	
	return 0;
}


#include "stdafx.h"
#include "DataExtractor.h"

#include <fstream>

using namespace std;

GraphData DataExtractor::extractDataFrom(const std::string& inputFileName)
{
	ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open()) {
		const string msg = "File " + inputFileName + " not opened";
		throw new exception(msg.c_str());
	}

	size_t vertexAmount;
	size_t arcAmount;
	size_t startVertex;
	inputFile >> vertexAmount;
	inputFile >> arcAmount;
	inputFile >> startVertex;

	convertToArrayIndex(startVertex);

	MyGraph graph = extractGraphFrom(inputFile, vertexAmount, arcAmount);
	return GraphData(vertexAmount, arcAmount, startVertex, graph);
}

MyGraph DataExtractor::extractGraphFrom(
	std::ifstream & inputFile,
	const size_t nodeAmount,
	const size_t roadAmount
)
{
	MyGraph graph = MyGraph(nodeAmount);
	for (size_t index = 0; index < roadAmount; ++index)
	{
		if (inputFile.eof()) {
			throw new exception("File end");
		}
		size_t from;
		size_t to;
		size_t distance;

		inputFile >> from;
		inputFile >> to;
		inputFile >> distance;

		convertToArrayIndex(from);
		convertToArrayIndex(to);

		graph.addPath(from, to, distance);
	}
	return graph;
}

void DataExtractor::convertToArrayIndex(size_t & number)
{
	--number;
}
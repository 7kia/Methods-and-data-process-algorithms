#pragma once
#include <vector>
#include <string>

#include "MyGraph.h"

struct GraphData 
{
	GraphData(
		const size_t vertexAmount,
		const size_t arcAmount,
		const size_t startVertex,
		const MyGraph graph
	) 
	{
		this->vertexAmount = vertexAmount;
		this->arcAmount = arcAmount;
		this->startVertex = startVertex;
		this->graph = graph;
	}
	size_t vertexAmount;
	size_t arcAmount;
	size_t startVertex;
	MyGraph graph = MyGraph(1);
};

class DataExtractor
{
public:
	static GraphData extractDataFrom(const std::string & inputFileName);
private:
	static MyGraph extractGraphFrom(std::ifstream & inputFile, const size_t nodeAmount, const size_t roadAmount);
	static void convertToArrayIndex(size_t & number);
};


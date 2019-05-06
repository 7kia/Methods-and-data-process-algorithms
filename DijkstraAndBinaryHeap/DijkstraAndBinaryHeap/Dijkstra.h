#pragma once

#include <vector>
#include <utility>// std::pair, std::make_pair
#include <iostream>// std::cout, std::endl
#include <limits>
#include <fstream>

#include "MyGraph.h"
#include "BinaryHeap.h"

struct InputData
{
	InputData(
		const size_t from,
		const size_t to,
		const MyGraph graph
	)
	{
		this->from = from;
		this->to = to;
		this->graph = graph;
	}
	size_t from;
	size_t to;
	MyGraph graph = MyGraph(0);
};

struct DataForPath
{
	DataForPath(
		const size_t previousVertexIndex,
		const std::vector<size_t> vertexes,
		const size_t minDistance,
		const size_t from,
		const size_t to
	) {
		this->previousVertexIndex = previousVertexIndex;
		this->vertexes = vertexes;
		this->minDistance = minDistance;
		this->from = from;
		this->to = to;
	}
	size_t previousVertexIndex;
	std::vector<size_t> vertexes;
	size_t minDistance;
	size_t from;
	size_t to;
};



class Dijkstra 
{
public:
	std::string findMinPath(const std::string& inputFileName);	
	std::string findMinPath(const size_t from, const size_t to, const MyGraph graph);
	static DataForPath recoveryPath(
		const MyGraph& graph,
		const std::vector<size_t>& minDistance,
		const size_t from,
		const size_t to
	);
private:
	InputData extractDataFrom(const std::string & inputFileName);
	MyGraph extractGraphFrom(
		std::ifstream & inputFile,
		const size_t nodeAmount,
		const size_t roadAmount
	);
	void convertToArrayIndex(size_t& number);
	void initVertexesAndDistances(const size_t from, const size_t size);
private:
	std::vector<size_t> m_minDistance;
};
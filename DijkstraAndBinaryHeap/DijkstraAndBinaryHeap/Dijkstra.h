#pragma once

#include <vector>
#include <utility>// std::pair, std::make_pair
#include <iostream>// std::cout, std::endl
#include <limits>
#include "MyGraph.h"

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
	static std::string findMinPath(const size_t from, const size_t to, const MyGraph graph);
	static DataForPath recoveryPath(
		const MyGraph& graph,
		const std::vector<size_t>& minDistance,
		const size_t from,
		const size_t to
	);
};
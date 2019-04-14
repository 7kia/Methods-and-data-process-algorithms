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

struct VertexDistance
{
	VertexDistance(const size_t index, const size_t distance)
	{
		this->index = index;
		this->distance = distance;
	}
	size_t index;
	size_t distance;
};
bool operator<(const VertexDistance& first, const VertexDistance& second);
bool operator<=(const VertexDistance& first, const VertexDistance& second);

class Dijkstra 
{
public:
	std::string findMinPath(const size_t from, const size_t to, const MyGraph graph);
	static DataForPath recoveryPath(
		const MyGraph& graph,
		const std::vector<size_t>& minDistance,
		const size_t from,
		const size_t to
	);
private:
	void updateMinDistanceForVertexes(const size_t size, size_t & min, size_t & minIndex);
	void initVertexesAndDistances(const size_t from, const size_t size);
	void findMinDistanceFromVertex(size_t & min, size_t & minIndex, const MyGraph graph);
private:
	std::vector<size_t> m_minDistance;
	std::vector<bool> m_markedVertexes;
};
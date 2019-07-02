#pragma once
#include "MyGraph.h"

#include <vector>
#include <string>


struct MaxPathData: public Edge
{
	std::vector<int> path;
	MaxPathData() {};

	MaxPathData(
		const size_t from,
		const size_t to,
		const int length,
		const std::vector<int>& path
	)
	{
		this->from = from;
		this->to = to;
		this->length = length;
		this->path = path;
	}
};

class BellmanFordAlgorithm
{
public:
	static const int NOT_VERTEX = -1;
public:
	static std::vector<MaxPathData> getMaxPaths(const MyGraph& graph, const size_t startVertex);
	static void handleArcs(
		std::vector<int>& maxPathWithPathLength,
		const std::vector<Edge>& edges,
		const size_t arcAmount,
		std::vector<int>& previousVertex,
		int& startNegativeCycle
	);

	static void printToConsoleNegativeCycles(
		const size_t startNegativeCycle,
		const std::vector<int>& previousVertex,
		const size_t startVertex,
		const size_t vertexAmount
	);
	static std::vector<MaxPathData> generateMaxPathData(
		const std::vector<int>& maxPathWithPathLength,
		const std::vector<int>& previousVertex,
		const size_t startVertex
	);

	static std::string printPath(const MaxPathData& data, const bool beautifulOutput);
	static void setBeautifulOutput(const MaxPathData& data, std::stringstream & result);
	static void addPath(
		const std::vector<size_t>& path,
		std::stringstream & result,
		const std::string delimiter
	);
};


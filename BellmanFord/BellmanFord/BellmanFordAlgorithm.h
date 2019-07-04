#pragma once
#include "MyGraph.h"

#include <vector>
#include <string>




class BellmanFordAlgorithm
{
public:
	typedef std::vector<MaxPathData> MaxPaths;
	static const int NOT_VERTEX = -1;
public:
	static MaxPaths getMaxPaths(const MyGraph& graph, const size_t startVertex);

private:
	static void handleArcs(
		std::vector<int>& maxPathWithPathLength,
		const std::vector<Edge>& edges,
		const size_t arcAmount,
		std::vector<int>& previousVertex,
		int& startNegativeCycle
	);
	static void printToConsoleNegativeCycles(
		const size_t startNegativeCycle,
		std::vector<int>& previousVertex,
		const size_t startVertex,
		const size_t vertexAmount
	);
	static std::vector<MaxPathData> generateMaxPathData(
		const std::vector<int>& maxPathWithPathLength,
		const std::vector<int>& previousVertex,
		const size_t startVertex
	);
	static std::vector<int> generatePath(
		const size_t from,
		const size_t to,
		const std::vector<int>& previousVertex
	);
	static int convertFromIndexToNaturalNumber(const int index);


};


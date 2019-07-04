#include "stdafx.h"
#include "BellmanFordAlgorithm.h"

#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

BellmanFordAlgorithm::MaxPaths BellmanFordAlgorithm::getMaxPaths(const MyGraph & graph, const size_t startVertex)
{
	std::vector<Edge> edges = graph.getEdges();
	size_t vertexAmount = graph.m_transitions.size();
	size_t arcAmount = graph.arcCount;

	vector<int> maxPathWithPathLength(vertexAmount, std::numeric_limits<int>::min());
	maxPathWithPathLength[startVertex] = 0;
	vector<int> previousVertex(vertexAmount, NOT_VERTEX);

	int startNegativeCycle;
	for (int vertexIndex = 0; vertexIndex < vertexAmount; ++vertexIndex) {
		startNegativeCycle = -1;
		handleArcs(
			maxPathWithPathLength,
			edges,
			arcAmount,
			previousVertex,
			startNegativeCycle
		);

	}
	printToConsoleNegativeCycles(
		startNegativeCycle,
		previousVertex,
		startVertex,
		vertexAmount
	);


	return generateMaxPathData(maxPathWithPathLength, previousVertex, startVertex);
}

void BellmanFordAlgorithm::handleArcs(
	vector<int>& maxPathWithPathLength,
	const vector<Edge>& edges,
	const size_t arcAmount,
	vector<int>& previousVertex,
	int& startNegativeCycle
)
{
	for (int arcCount = 0; arcCount < arcAmount; ++arcCount) {
		const Edge& currentEdge = edges[arcCount];

		const bool pathExist = maxPathWithPathLength[currentEdge.from] > std::numeric_limits<int>::min();
		const int newLength = maxPathWithPathLength[currentEdge.from] + currentEdge.length;
		const bool pathLonger = maxPathWithPathLength[currentEdge.to] < newLength;
		if (pathExist && pathLonger) {
			maxPathWithPathLength[currentEdge.to] = max(
				std::numeric_limits<int>::min(),
				newLength
			);	
			previousVertex[currentEdge.to] = static_cast<int>(currentEdge.from);
			startNegativeCycle = static_cast<int>(currentEdge.to);
		}
	}
}

void BellmanFordAlgorithm::printToConsoleNegativeCycles(
	const size_t startNegativeCycle,
	vector<int>& previousVertex,
	const size_t startVertex, 
	const size_t vertexAmount
)
{
	if (startNegativeCycle == -1) {
		cout << "No negative cycle from " << startVertex + 1 << endl;
	}
	else {
		int y = static_cast<int>(startNegativeCycle);
		for (int i = 0; i < vertexAmount; ++i) {
			y = previousVertex[y];
		}

		vector<int> path;
		for (int cur = y; ; cur = previousVertex[cur]) {
			path.push_back(cur);
			if (cur == y && path.size() > 1) {
				break;
			}
		}
		reverse(path.begin(), path.end());

		const int cycleVertexIndex = path[1];
		previousVertex[cycleVertexIndex] = NOT_VERTEX;

		cout << "Negative cycle: ";
		for (size_t i = 0; i < path.size(); ++i)
		{
			cout << path[i] + 1 << ' ';
		}
		cout << endl;
	}
}

BellmanFordAlgorithm::MaxPaths BellmanFordAlgorithm::generateMaxPathData(
	const std::vector<int>& maxPathWithPathLength,
	const std::vector<int>& previousVertex,
	const size_t startVertex
)
{
	std::vector<MaxPathData> result = std::vector<MaxPathData>();

	for (size_t vertexIndex = 0; vertexIndex < maxPathWithPathLength.size(); ++vertexIndex)
	{
		if (vertexIndex == startVertex)
		{
			result.push_back(MaxPathData(vertexIndex, vertexIndex, 0, vector<int>()));
		}
		else
		{
			result.push_back(
				MaxPathData(
					startVertex,
					vertexIndex, 
					maxPathWithPathLength[vertexIndex],
					generatePath(startVertex, vertexIndex, previousVertex)
				)
			);
		}
	}

	return result;
}

vector<int> BellmanFordAlgorithm::generatePath(
	const size_t from, 
	const size_t to, 
	const std::vector<int>& previousVertex
)
{
	vector<int> path;
	for (int cur = static_cast<int>(to); ; cur = previousVertex[cur]) {
		if (cur == NOT_VERTEX) {
			return vector<int>();
		}
		if (path.size() >= previousVertex.size()) {
			break;
		}

		path.push_back(convertFromIndexToNaturalNumber(cur));
		const bool isEnd = (cur == from);
		if (isEnd && (path.size() > 1)) {
			break;
		}
	}
	reverse(path.begin(), path.end());
	return path;
}

int BellmanFordAlgorithm::convertFromIndexToNaturalNumber(const int index)
{
	return index + 1;
}


#include "stdafx.h"
#include "BellmanFordAlgorithm.h"

#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

std::vector<MaxPathData> BellmanFordAlgorithm::getMaxPaths(const MyGraph & graph, const size_t startVertex)
{
	std::vector<Edge> edges = graph.getEdges();
	size_t vertexAmount = graph.m_transitions.size();
	size_t arcAmount = graph.arcCount;

	vector<int> maxPathWithPathLength(vertexAmount, std::numeric_limits<int>::infinity());
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

		const bool pathExist = maxPathWithPathLength[currentEdge.from] < std::numeric_limits<int>::infinity();
		const int newLength = maxPathWithPathLength[currentEdge.from] + currentEdge.length;
		const bool pathLonger = maxPathWithPathLength[currentEdge.to] < newLength;
		if (pathExist && pathLonger) {
			maxPathWithPathLength[currentEdge.to] = max(
				-std::numeric_limits<int>::infinity(),
				newLength
			);
			previousVertex[currentEdge.to] = currentEdge.from;
			startNegativeCycle = currentEdge.to;
		}
	}
}

//BellmanFordAlgorithm::MaxPathWithPathLength BellmanFordAlgorithm::initShortPaths(
//	const size_t vertexAmount,
//	const size_t arcAmount,
//	const size_t startVertex
//)
//{
//	MaxPathWithPathLength maxPathWithPathLength = MaxPathWithPathLength(arcAmount - 1);
//	for (size_t arcCount = 0; arcCount < maxPathWithPathLength.size(); ++arcCount)
//	{
//		maxPathWithPathLength[arcCount] = MaxVertexPath(vertexAmount);
//		MaxVertexPath& maxVertexPath = maxPathWithPathLength[arcCount];
//		for (size_t vertexIndex = 0; vertexIndex < maxPathWithPathLength[arcCount].size(); ++vertexIndex)
//		{
//			if (vertexIndex == startVertex)
//			{
//				maxVertexPath[vertexIndex] = Edge(0, vertexIndex);// TODO: из-за второго аргумента возможны баги
//			} 
//			else
//			{
//				maxVertexPath[vertexIndex] = Edge(std::numeric_limits<size_t>::infinity(), std::numeric_limits<size_t>::infinity());
//			}
//		}
//	}
//	return MaxPathWithPathLength();
//}


void BellmanFordAlgorithm::printToConsoleNegativeCycles(
	const size_t startNegativeCycle,
	const vector<int>& previousVertex,
	const size_t startVertex, 
	const size_t vertexAmount
)
{
	if (startNegativeCycle == -1) {
		cout << "No negative cycle from " << startVertex;
	}
	else {
		int y = startNegativeCycle;
		for (int i = 0; i < vertexAmount; ++i) {
			y = previousVertex[y];
		}

		vector<int> path;
		for (int cur = y; ; cur = previousVertex[cur]) {
			path.push_back(cur);
			if (cur == y && path.size() > 1)  break;
		}
		reverse(path.begin(), path.end());

		cout << "Negative cycle: ";
		for (size_t i = 0; i < path.size(); ++i)
		{
			cout << path[i] << ' ';
		}

	}
}

std::vector<MaxPathData> BellmanFordAlgorithm::generateMaxPathData(
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
			result.push_back(generatePath());
		}
	}

	return result;
}


std::string BellmanFordAlgorithm::printPath(const MaxPathData& data, const bool beautifulOutput)
{
	std::stringstream result;
	if (beautifulOutput) {
		setBeautifulOutput(data, result);
	}
	else
	{
		if (data.length)
		{
			result << data.length << " " << data.path.size() << " ";
			addPath(data.path, result, " ");
		}
		else
		{
			result << "No";
		}
	}
	result << "\n";
	return result.str();
}

void BellmanFordAlgorithm::setBeautifulOutput(const MaxPathData & data, std::stringstream & result)
{
	if (data.length)
	{
		result << data.from + 1 << " to " << data.to + 1 << ";";
		result << "Length = " << data.length << "Vertex amount =" << data.path.size() << "\n";

		result << "Path: ";
		addPath(data.path, result, " => ");
	}
	else
	{
		result << "Path from " << data.from << " to " << data.to << " not exist";
	}
}

void BellmanFordAlgorithm::addPath(
	const std::vector<size_t>& path,
	std::stringstream & result,
	const std::string delimiter
)
{
	for (size_t i = 0; i < path.size(); ++i)
	{
		result << path[i];
		if ((i + 1) < path.size())
		{
			result << delimiter;
		}
	}
}

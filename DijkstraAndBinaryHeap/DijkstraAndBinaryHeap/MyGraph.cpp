#include "stdafx.h"
#include "MyGraph.h"
#include "Dijkstra.h"

using namespace std;

MyGraph::MyGraph(const size_t vertexAmount)
{
	m_transitionMatrix = vector<vector<size_t>>(vertexAmount);
	for (int i = 0; i < vertexAmount; i++)
	{
		m_transitionMatrix[i] = vector<size_t>(vertexAmount);
		m_transitionMatrix[i][i] = 0;
	}
}

MyGraph::~MyGraph()
{
}

void MyGraph::addPath(const size_t from, const size_t to, const size_t disatance)
{
	m_transitionMatrix[to][from] = disatance;
}

void MyGraph::addBidirectionalPath(const size_t from, const size_t to, const size_t disatance)
{
	this->addPath(from, to, disatance);
	this->addPath(to, from, disatance);
}

std::string MyGraph::print()
{
	string result;
	for each (vector<size_t> row in m_transitionMatrix)
	{
		for each (size_t distance in row)
		{
			result.append(std::to_string(distance) + " ");
		}
		result.append("\n");
	}
	result.append("\n");
	return result;
}

std::string MyGraph::printPath(const DataForPath data) const
{
	const std::vector<size_t>& vertexes = data.vertexes;
	const size_t previousVertexIndex = data.previousVertexIndex;
	const size_t minDistance = data.minDistance;

	string result = "Path from " + to_string(data.from) + " to " + to_string(data.to) + "; ";
	for (int i = static_cast<int>(previousVertexIndex - 1); i >= 0; i--)
	{
		result.append(to_string(vertexes[i]));
		if ((i - 1) >= 0)
		{
			result.append(" => ");
		}
	}

	result.append(" Distance = " + to_string(minDistance));
	return result;
}

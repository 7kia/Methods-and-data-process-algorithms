#include "stdafx.h"
#include "MyGraph.h"
#include "Dijkstra.h"

using namespace std;

MyGraph::MyGraph(const size_t vertexAmount)
{
	m_transitions = vector<vector<VertexDistance>>(vertexAmount);
}

MyGraph::~MyGraph()
{
}

void MyGraph::addPath(const size_t from, const size_t to, const size_t distance)
{
	m_transitions[from].push_back(VertexDistance(to, distance));
}

void MyGraph::addBidirectionalPath(const size_t from, const size_t to, const size_t distance)
{
	this->addPath(from, to, distance);
	this->addPath(to, from, distance);
}

std::string MyGraph::print()
{
	string result;
	for (size_t index = 0; index < m_transitions.size(); ++index)
	{
		vector<VertexDistance> row = m_transitions[index];
		result.append("From vertex \"" + std::to_string(index) + "\" : ");
		for each (VertexDistance vertex in row)
		{
			result.append("to +\"" + std::to_string(vertex.index) + "\" distance = " + std::to_string(vertex.distance) + "; ");
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

	string result = "Path from " + to_string(data.from + 1) + " to " + to_string(data.to + 1) + ";\n";
	for (int i = static_cast<int>(previousVertexIndex - 1); i >= 0; i--)
	{
		result.append(to_string(vertexes[i]));
		if ((i - 1) >= 0)
		{
			result.append(" => ");
		}
	}

	result.append("\nDistance = " + to_string(minDistance));
	return result;
}



bool operator<(const VertexDistance& first, const VertexDistance& second)
{
	return first.distance < second.distance;
}

bool operator<=(const VertexDistance& first, const VertexDistance& second)
{
	return first.distance <= second.distance;
}
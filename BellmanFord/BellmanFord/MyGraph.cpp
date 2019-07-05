#include "stdafx.h"
#include "MyGraph.h"

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
	++arcCount;
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

std::vector<Edge> MyGraph::getEdgeList() const
{
	std::vector<Edge> result = std::vector<Edge>();
	for (size_t i = 0; i < m_transitions.size(); ++i)
	{
		const std::vector<VertexDistance>& transitions = m_transitions[i];
		for (size_t j = 0; j < transitions.size(); ++j)
		{
			result.push_back(
				Edge(
					i,
					transitions[j].index,
					transitions[j].distance
				)
			);
		}
	}
	return result;
}

std::vector<std::vector<Edge>> MyGraph::getEdges() const
{
	std::vector<std::vector<Edge>> result = std::vector<std::vector<Edge>>(m_transitions.size());
	for (size_t i = 0; i < m_transitions.size(); ++i)
	{
		const std::vector<VertexDistance>& transitions = m_transitions[i];
		for (size_t j = 0; j < transitions.size(); ++j)
		{
			result[i].push_back(
				Edge(
					i,
					transitions[j].index,
					transitions[j].distance
				)
			);
		}
	}
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
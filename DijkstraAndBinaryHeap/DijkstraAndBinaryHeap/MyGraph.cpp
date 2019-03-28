#include "stdafx.h"
#include "MyGraph.h"

using namespace std;

MyGraph::MyGraph(const size_t vertexAmount)
{
	m_transitionMatrix = vector<vector<size_t>>(vertexAmount);
	for (int i = 0; i < vertexAmount; i++)
	{
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
	}
	result.append("\n");
	return result;
}

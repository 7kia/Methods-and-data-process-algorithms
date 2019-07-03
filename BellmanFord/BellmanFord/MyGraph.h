#pragma once

#include <vector>
#include <string>

struct DataForPath;

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
struct Edge {
	size_t from = 0;
	size_t to = 0;
	int length = 0;

	Edge() {};

	Edge(
		const size_t from,
		const size_t to,
		const int length
	)
	{
		this->from = from;
		this->to = to;
		this->length = length;
	}
};
struct MaxPathData : public Edge
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

bool operator<(const VertexDistance& first, const VertexDistance& second);
bool operator<=(const VertexDistance& first, const VertexDistance& second);

class MyGraph
{
public:
	MyGraph(const size_t vertexAmount);
	~MyGraph();

	// Warning: vertex number(from, to) start on 1
	void addPath(const size_t from, const size_t to, const size_t disatance);
	// Warning: vertex number(from, to) start on 1
	void addBidirectionalPath(const size_t from, const size_t to, const size_t disatance);
	std::string print();
	std::vector<Edge> getEdges() const;
public:
	std::vector<std::vector<VertexDistance>> m_transitions;
	size_t arcCount = 0;
};

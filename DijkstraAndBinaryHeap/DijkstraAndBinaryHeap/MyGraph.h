#pragma once

#include <vector>
#include <string>

struct MyStruct
{

};

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
public:
	std::vector<std::vector<size_t>> m_transitionMatrix;
};


#pragma once
#include "MyGraph.h"

#include <vector>
#include <string>

struct MaxPathData
{
	size_t from = 0;
	size_t to = 0;
	size_t length = 0;
	std::vector<size_t> path;

	MaxPathData() {};

	MaxPathData(
		const size_t from,
		const size_t to,
		const size_t length,
		const std::vector<size_t> path
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
	static std::vector<MaxPathData> getMaxPaths(const MyGraph& graph);
	static std::string printPath(const MaxPathData& data, const bool beautifulOutput);
	static void setBeautifulOutput(const MaxPathData& data, std::stringstream & result);
	static void addPath(
		const std::vector<size_t>& path,
		std::stringstream & result,
		const std::string delimiter
	);
};


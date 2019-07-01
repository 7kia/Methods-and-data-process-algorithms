#include "stdafx.h"
#include "BellmanFordAlgorithm.h"

#include <sstream>


using namespace std;
vector<MaxPathData> BellmanFordAlgorithm::getMaxPaths(const MyGraph & graph)
{
	vector<MaxPathData> result = vector<MaxPathData>(2);
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

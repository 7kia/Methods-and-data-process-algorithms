#include "stdafx.h"
#include "MaxPathPrinter.h"

std::string MaxPathPrinter::printPath(const MaxPathData& data, const bool beautifulOutput) const
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

void MaxPathPrinter::setBeautifulOutput(const MaxPathData & data, std::stringstream & result) const
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

void MaxPathPrinter::addPath(
	const std::vector<int>& path,
	std::stringstream & result,
	const std::string delimiter
) const
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

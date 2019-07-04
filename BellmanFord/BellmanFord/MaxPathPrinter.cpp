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
		if (data.length > 0)
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
	if (data.length > 0)
	{
		result << convertFromIndexToNaturalNumber(data.from) << " to " << convertFromIndexToNaturalNumber(data.to) << ";";
		result << "Length = " << data.length << "; Vertex amount =" << data.path.size() << "\n";

		result << "Path: ";
		addPath(data.path, result, " => ");
	}
	else
	{
		result << "Path from " << convertFromIndexToNaturalNumber(data.from)
			<< " to " << convertFromIndexToNaturalNumber(data.to) << " not exist";
	}
}

size_t MaxPathPrinter::convertFromIndexToNaturalNumber(const size_t index) const
{
	return index + 1;
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

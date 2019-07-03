#pragma once
#include <string>
#include <iostream>
#include <sstream>

#include "MyGraph.h"

class MaxPathPrinter
{
public:
	std::string printPath(const MaxPathData& data, const bool beautifulOutput) const;
private:
	void setBeautifulOutput(const MaxPathData& data, std::stringstream & result) const;
	void addPath(
		const std::vector<int>& path,
		std::stringstream & result,
		const std::string delimiter
	) const;
};


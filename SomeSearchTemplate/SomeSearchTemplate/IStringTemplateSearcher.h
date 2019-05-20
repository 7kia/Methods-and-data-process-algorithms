#pragma once
#include <vector>

#include "DataExtractor.h"

struct FoundTemplate
{
	FoundTemplate(
		const size_t stringNumber,
		const size_t position
	) 
	{
		this->stringNumber = stringNumber;
		this->position = position;
	}
	size_t stringNumber;
	size_t position;
};
typedef std::vector<size_t> FoundPositions;

class IStringTemplateSearcher
{
public:
	virtual std::vector<std::vector<FoundPositions>> foundTemplates(const TemplateSearchData data) = 0;
};

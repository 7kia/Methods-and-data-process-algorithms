#pragma once
#include "IStringTemplateSearcher.h"

class AhoKorasikAlgorithm : public IStringTemplateSearcher
{
public:
	std::vector<std::vector<FoundPositions>> foundTemplates(const TemplateSearchData data);
};


#pragma once
#include "IStringTemplateSearcher.h"

class AhoKorasikAlgorithm : public IStringTemplateSearcher
{
public:
	std::vector<FoundTemplate> foundTemplates(const TemplateSearchData data);
};


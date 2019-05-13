#pragma once
#include "IStringTemplateSearcher.h"

class RabbiCarpAlgorithm: public IStringTemplateSearcher
{
public:
	std::vector<FoundTemplate> foundTemplates(const TemplateSearchData data);
};


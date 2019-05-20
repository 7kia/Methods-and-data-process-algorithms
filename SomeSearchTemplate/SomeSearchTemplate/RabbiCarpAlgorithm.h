#pragma once
#include "IStringTemplateSearcher.h"
#include "HashFunction.h"

#include <vector>

class RabbiCarpAlgorithm: public IStringTemplateSearcher
{
public:
	const size_t MAX_STRING_SIZE = 256;

	std::vector<std::vector<FoundPositions>> foundTemplates(const TemplateSearchData data);
	std::vector<size_t> getTemplateSizes(const std::vector<std::string>& templates);
private:
	std::vector<std::string> toLowerCase(const std::vector<std::string> templates);
private:
	HashFunction m_hashFunction = HashFunction(MAX_STRING_SIZE);
};


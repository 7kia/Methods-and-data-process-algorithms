#pragma once
#include "IStringTemplateSearcher.h"
#include "HashFunction.h"

#include <vector>

struct TemplateData
{
	std::vector<std::string> templates;
	std::vector<size_t> templateSizes;
	size_t maxTemplateLength;
	std::vector<Hash> templateHashs;


	TemplateData(
		const std::vector<std::string> templates,
		const std::vector<size_t> templateSizes,
		const size_t maxTemplateLength,
		const std::vector<Hash> templateHashs
	) {
		this->templates = templates;
		this->templateSizes = templateSizes;
		this->maxTemplateLength = maxTemplateLength;
		this->templateHashs = templateHashs;
	}
};

class RabbiCarpAlgorithm: public IStringTemplateSearcher
{
public:
	const size_t MAX_STRING_SIZE = 256;

	std::vector<std::vector<FoundPositions>> foundTemplates(const TemplateSearchData data);
	std::vector<size_t> getTemplateSizes(const std::vector<std::string>& templates);
private:
	void handleString(
		const std::string& inputString,
		std::vector< std::vector<FoundPositions>>& foundTemplates,
		const TemplateData& templateData,
		const size_t endCompareIndex
	);
	bool foundSecondStringAndHandle(
		std::ifstream &inputFile,
		const std::string& string1,
		const TemplateData& templateData,
		std::vector<std::vector<FoundPositions>>& result
	);
	std::vector<std::string> toLowerCase(const std::vector<std::string> templates);
	std::string toLowerCase(const std::string string);
private:
	HashFunction m_hashFunction = HashFunction(MAX_STRING_SIZE);
};


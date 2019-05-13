#include "stdafx.h"
#include "DataExtractor.h"

TemplateSearchData DataExtractor::extractData(const std::string fileName)
{
	size_t templateAmount = 0;
	std::vector<std::string> templates = std::vector<std::string>();
	std::string inputFileName = fileName;

	return TemplateSearchData(templateAmount, templates, fileName);
}

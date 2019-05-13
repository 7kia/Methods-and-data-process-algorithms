#pragma once
#include <vector>
#include <string>

struct TemplateSearchData 
{
	TemplateSearchData(
		const size_t templateAmount,
		const std::vector<std::string> templates,
		const std::string fileName
	) {
		this->templateAmount = templateAmount;
		this->templates = templates;
		this->fileName = fileName;
	}
	size_t templateAmount;
	std::vector<std::string> templates;
	std::string fileName;
};

class DataExtractor
{
public:
	static TemplateSearchData extractData(const std::string fileName);
};


#include "stdafx.h"
#include "HashFunction.h"

#include <math.h>

using namespace std;

HashFunction::HashFunction(const size_t maxStringSize)
{
	//pow(COEFFICIENT, p_pow.size() - 1);
	// TODO: нужно расчитать заранее, возможно из-за этого будет ошибка
	p_pow = vector<size_t>(maxStringSize);
	p_pow[0] = 1;
	for (size_t i = 1; i < p_pow.size(); ++i) {
		p_pow[i] = p_pow[i - 1] * COEFFICIENT;
	}
}


HashFunction::~HashFunction()
{
}

vector<Hash> HashFunction::getPrefixesHashs(const std::string string)
{
	vector<Hash> hash(string.length());
	for (size_t i = 0; i < string.length(); ++i)
	{
		hash[i] = getHash(string[i], i);
		if (i) {
			hash[i] += hash[i - 1];
		}
	}
	return hash;
}

std::vector<Hash> HashFunction::getHashs(const std::vector<std::string>& templates)
{
	std::vector<Hash> hashs;
	for (size_t i = 0; i < templates.size(); ++i)
	{
		hashs.push_back(getHash(templates[i]));
	}
	return hashs;
}

Hash HashFunction::getHash(const std::string string)
{
	Hash hash = 0;
	for (size_t i = 0; i < string.length(); ++i) {
		hash += getHash(string[i], i);
	}
	return hash;
}

Hash HashFunction::getHash(const char symbol, const size_t index)
{
	return (symbol - 'a' + 1) * p_pow[index];
}



std::vector<FoundPositions> HashFunction::compare(
	const std::vector<Hash>& templateHashs,
	const std::vector<size_t>& templateSizes,
	const size_t maxTemplateSize,
	const std::string& text,
	const size_t endCompareIndex
) {
	vector<Hash> textHash = getPrefixesHashs(text);

	vector<FoundPositions> positions = vector<FoundPositions>(templateHashs.size());
	// TODO: отсортировать хэши шаблонов по длинам(на подобие списков смежности)

	// перебираем все подстроки T длины |S| и сравниваем их
	for (size_t tempIndex = 0; tempIndex < templateHashs.size(); tempIndex++)
	{
		const Hash searhTemplateHash = templateHashs[tempIndex];

		for (size_t i = 0; (i < endCompareIndex) && ((i + templateSizes[tempIndex] - 1) < text.size()); ++i)
		{
			Hash sliceHash = getSliceHash(textHash, i, templateSizes[tempIndex]);
			const Hash approximateHash = searhTemplateHash * p_pow[i];
			if (sliceHash == approximateHash) {
				positions[tempIndex].push_back(i);
			}
		}
	}

	return positions;
}

Hash HashFunction::getSliceHash(const std::vector<Hash> & textHash, const size_t startIndex, const size_t templateLength)
{
	Hash hash = textHash[startIndex + templateLength - 1];
	if (startIndex) {
		hash -= textHash[startIndex - 1];
	}

	return hash;
}

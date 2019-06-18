#pragma once
#include <string>
#include <vector>

typedef size_t Hash;
typedef std::vector<size_t> FoundPositions;

class HashFunction
{
public:
	HashFunction(const size_t maxStringSize);
	~HashFunction();

	std::vector<Hash> getPrefixesHashs(const std::string string);
	std::vector<Hash> getHashs(const std::vector<std::string>& templates);

	Hash getHash(const std::string string);
	Hash getHash(const char symbol, const size_t index);

	std::vector<FoundPositions> compare(
		const std::vector<Hash>& templateHashs,
		const std::vector<size_t>& templateSizes,
		const size_t maxTemplateSize,
		const std::string& text,
		const size_t endCompareIndex
	);
private:
	Hash getSliceHash(const std::vector<Hash> & textHash, const size_t startIndex, const size_t templateLength);
public:
	const size_t COEFFICIENT = 31;
	std::vector<size_t> p_pow;// TODO: rename
};


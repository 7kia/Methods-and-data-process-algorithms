#include "stdafx.h"
#include "BinaryHeap.h"

using namespace std;

std::string printAsHeap(std::vector<int> heapContent)
{
	string result = "";
	int i = 0;
	int k = 1;
	while (i < heapContent.size()) {
		while ((i < k) && (i < heapContent.size())) {
			result.append(std::to_string(heapContent[i]) + " ");
			i++;
		}
		result.append("\n");
		k = k * 2 + 1;
	}

	return result;
}

std::string printAsArray(std::vector<int> heapContent)
{
	string result = "";
	for each (int var in heapContent)
	{
		result.append(std::to_string(var) + " ");
	}

	result += "\n";
	return result;
}


bool operator<(const VertexDistance& first, const VertexDistance& second)
{
	return first.distance < second.distance;
}

bool operator<=(const VertexDistance& first, const VertexDistance& second)
{
	return first.distance <= second.distance;
}

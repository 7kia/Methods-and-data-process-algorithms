#include "stdafx.h"
#include "BinaryHeap.h"

using namespace std;
BinaryHeap::BinaryHeap(const size_t size)
{
	heapContent = vector<int>(size);
	heapSize = 0;
}


BinaryHeap::~BinaryHeap()
{
}

void BinaryHeap::addElement(const int element)
{
	size_t i;
	size_t parent;
	i = heapSize;
	heapContent[i] = element;
	parent = (i - 1) / 2;
	while (parent >= 0 && i > 0) {
		if (heapContent[i] < heapContent[parent]) {
			swap(heapContent[i], heapContent[parent]);
		}
		i = parent;
		parent = (i - 1) / 2;
	}
	heapSize++;
}

string BinaryHeap::printAsHeap()
{
	string result = "";
	int i = 0;
	int k = 1;
	while (i < heapSize) {
		while ((i < k) && (i < heapSize)) {
			result.append(std::to_string(heapContent[i]) + " ");
			i++;
		}
		result.append("\n");
		k = k * 2 + 1;
	}

	return result;
}

string BinaryHeap::printAsArray()
{
	string result = "";
	for each (int var in heapContent)
	{
		result.append(std::to_string(var) + " ");
	}

	result += "\n";
	return result;
}

int BinaryHeap::getMin()
{
	int max = heapContent[0];
	heapContent[0] = heapContent[heapSize - 1];
	heapSize--;
	seed(0);
	return max;
}

void BinaryHeap::seed(const int elementIndex)
{
	int left;
	int right;
	left = 2 * elementIndex + 1;
	right = 2 * elementIndex + 2;
	swapAndSeedNext(elementIndex, left);
	swapAndSeedNext(elementIndex, right);
}

void BinaryHeap::swapAndSeedNext(const int elementIndex, const int swapElement)
{
	if (swapElement < heapSize) {
		if (heapContent[elementIndex] > heapContent[swapElement]) {
			std::swap(heapContent[elementIndex], heapContent[swapElement]);
			seed(swapElement);
		}
	}
}

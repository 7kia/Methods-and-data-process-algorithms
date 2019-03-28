#include "stdafx.h"
#include "BinaryHeap.h"

using namespace std;
BinaryHeap::BinaryHeap()
{
	heapContent = vector<int>(this->SIZE);
	heapSize = 0;
}


BinaryHeap::~BinaryHeap()
{
}

void BinaryHeap::addelem(const int element)
{
	int i, parent;
	i = heapSize;
	heapContent[i] = element;
	parent = (i - 1) / 2;
	while (parent >= 0 && i > 0) {
		if (heapContent[i] > heapContent[parent]) {
			//int temp = heapContent[i];
			//heapContent[i] = heapContent[parent];
			//heapContent[parent] = temp;
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
			result += heapContent[i] + "» «";
			i++;
		}
		result += "\n";
		k = k * 2 + 1;
	}

	return result;
}

string BinaryHeap::printAsArray()
{
	string result = "";
	for (int i = 0; i < heapSize; i++) {
		result += heapContent[i] + "» «";
	}
	result += "\n";
	return result;
}

int BinaryHeap::getmax()
{
	int max = heapContent[0];
	heapContent[0] = heapContent[heapSize - 1];
	heapSize--;
	seed(0);
	return(max);
}

void BinaryHeap::seed(const int elementIndex)
{
	int left, right;
	int temp;
	left = 2 * elementIndex + 1;
	right = 2 * elementIndex + 2;
	swapAndSeedNext(elementIndex, left);
	swapAndSeedNext(elementIndex, right);
	//if (left < HeapSize) {
	//	if (h[elementIndex] < h[left]) {
	//		temp = h[elementIndex];
	//		h[elementIndex] = h[left];
	//		h[left] = temp;
	//		seed(left);
	//	}
	//}
	//if (right < HeapSize) {
	//	if (h[elementIndex] < h[right]) {
	//		temp = h[elementIndex];
	//		h[elementIndex] = h[right];
	//		h[right] = temp;
	//		seed(right);
	//	}
	//}
}

void BinaryHeap::swapAndSeedNext(const int elementIndex, const int swapElement)
{
	if (swapElement < heapSize) {
		if (heapContent[elementIndex] < heapContent[swapElement]) {
			//temp = h[elementIndex];
			//h[elementIndex] = h[swapElement];
			//h[swapElement] = temp;
			std::swap(heapContent[elementIndex], heapContent[swapElement]);
			seed(swapElement);
		}
	}
}

#include "stdafx.h"
#include "BinaryHeap.h"

using namespace std;

BinaryHeap::BinaryHeap()
{
}


BinaryHeap::~BinaryHeap()
{
}

void BinaryHeap::addElement(const int element)
{
	size_t i;
	size_t parent;
	heapContent.push_back(element);
	siftUp(heapContent.size() - 1);
}

void BinaryHeap::siftUp(const int index)
{
	int i = index;
	while (heapContent[i] < heapContent[(i - 1) / 2])// i  0 � �� � �����
	{
		swap(heapContent[i], heapContent[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void BinaryHeap::siftDown(const int index)
{
	int left;
	int right;
	int i = index;
	int j;
	while (2 * i + 1 < heapContent.size())  // heapSize � ���������� ��������� � ����
	{
		left = 2 * i + 1;             // left � ����� ���
		right = 2 * i + 2;            // right � ������ ���
		j = left;
		if ((right < heapContent.size()) && (heapContent[right] < heapContent[left]))
		{
			j = right;
		}
		if (heapContent[i] <= heapContent[j])
		{
			break;
		}
		swap(heapContent[i], heapContent[j]);
		i = j;
	}    		
}

string BinaryHeap::printAsHeap()
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

int BinaryHeap::getAndDeleteMin()
{
	int min = heapContent[0];
	heapContent[0] = heapContent[heapContent.size() - 1];
	heapContent.pop_back();	
	siftDown(0);
	return min;
}

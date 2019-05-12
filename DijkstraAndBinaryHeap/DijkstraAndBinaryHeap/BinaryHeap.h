#pragma once
#include <stdio.h>
#include <vector>
#include <string>

std::string printAsHeap(std::vector<int> heapContent);
std::string printAsArray(std::vector<int> heapContent);

template<class ElemType>
class BinaryHeap
{
public:
	std::vector<ElemType> heapContent;
public:
	//BinaryHeap();
	//~BinaryHeap();
	void addElement(const ElemType element)
	{
		heapContent.push_back(element);
		siftUp(heapContent.size() - 1);
	}

	void siftUp(const size_t index)
	{
		// TODO: поправить значение (i - 1) / 2 и его выход за пределы
		int i = static_cast<int>(index);
		
		while (heapContent[i] < heapContent[(i - 1) / 2])// i  0 — мы в корне
		{
			swap(heapContent[i], heapContent[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	void siftDown(const size_t index)
	{
		size_t left;
		size_t right;
		size_t i = index;
		size_t j;
		while ((2 * i + 1) < heapContent.size())
		{
			left = 2 * i + 1;
			right = 2 * i + 2;
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

	ElemType getAndDeleteMin()
	{
		ElemType min = heapContent[0];
		heapContent[0] = heapContent[heapContent.size() - 1];
		heapContent.pop_back();
		siftDown(0);
		return min;
	}

};


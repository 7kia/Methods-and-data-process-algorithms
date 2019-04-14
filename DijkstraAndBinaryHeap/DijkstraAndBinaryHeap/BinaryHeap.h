#pragma once
#include <stdio.h>
#include <vector>
#include <string>

typedef struct {
	// int value;
	int  key;
} Item;

class BinaryHeap
{
public:
	std::vector<int> heapContent;
public:
	BinaryHeap();
	~BinaryHeap();
	void addElement(const int element);
	void siftUp(const int index);
	void siftDown(const int index);
	std::string printAsHeap();
	std::string printAsArray();
	int getAndDeleteMin();
};


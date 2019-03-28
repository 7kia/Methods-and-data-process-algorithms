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
	static const size_t SIZE = 100; // максимальный размер кучи
	std::vector<int> heapContent;         // указатель на массив кучи
	size_t heapSize; // размер кучи
public:
	BinaryHeap(const size_t size);
	~BinaryHeap();
	void addelem(const int element);  // добавление элемента кучи
	std::string printAsHeap();  // вывод элементов кучи в форме кучи
	std::string printAsArray();  // вывод элементов кучи в форме массива
	int getmax();  // удаление вершины (максимального элемента)
	void seed(const int elementIndex);

private:
	void swapAndSeedNext(const int elementIndex, const int swapElement);
};


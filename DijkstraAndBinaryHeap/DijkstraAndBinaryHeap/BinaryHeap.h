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
	static const size_t SIZE = 100; // ������������ ������ ����
	std::vector<int> heapContent;         // ��������� �� ������ ����
	size_t heapSize; // ������ ����
public:
	BinaryHeap(const size_t size);
	~BinaryHeap();
	void addelem(const int element);  // ���������� �������� ����
	std::string printAsHeap();  // ����� ��������� ���� � ����� ����
	std::string printAsArray();  // ����� ��������� ���� � ����� �������
	int getmax();  // �������� ������� (������������� ��������)
	void seed(const int elementIndex);

private:
	void swapAndSeedNext(const int elementIndex, const int swapElement);
};


// DijkstraAndBinaryHeap.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"

#include "MyGraph.h"

#include <locale>

using namespace std;

const int INF = 1000000000;

int main() {
	setlocale(LC_ALL, "Russian");
	const size_t SIZE = 6;
	int transferMatrix[SIZE][SIZE]; // ������� ������
	int minDistance[SIZE]; // ����������� ����������
	int markedVertexes[SIZE]; // ���������� �������
	int temp;


	MyGraph graph = MyGraph(6);
	graph.addBidirectionalPath(1, 2, 7);
	graph.addBidirectionalPath(1, 3, 9);
	graph.addBidirectionalPath(1, 6, 14);
	graph.addBidirectionalPath(2, 3, 10);
	graph.addBidirectionalPath(2, 4, 15);
	graph.addBidirectionalPath(3, 4, 11);
	graph.addBidirectionalPath(3, 6, 2);
	graph.addBidirectionalPath(4, 5, 6);
	graph.addBidirectionalPath(5, 6, 9);

	//// ������������� ������� ������
	//for (int i = 0; i < SIZE; i++)
	//{
	//	transferMatrix[i][i] = 0;
	//	for (int j = i + 1; j < SIZE; j++) {
	//		printf("������� ���������� %d - %d: ", i + 1, j + 1);
	//		scanf_s("%d", &temp);
	//		transferMatrix[i][j] = temp;
	//		transferMatrix[j][i] = temp;
	//	}
	//}
	
	cout << graph.print() << endl;
	//// ����� ������� ������
	//for (int i = 0; i < SIZE; i++)
	//{
	//	for (int j = 0; j < SIZE; j++)
	//		printf("%5d ", transferMatrix[i][j]);
	//	printf("\n");
	//}

	
	// ����� ���������� ���������� �� ������
	printf("\n���������� ���������� �� ������: \n");
	for (int i = 0; i < SIZE; i++)
		printf("%5d ", minDistance[i]);

	// �������������� ����
	int ver[SIZE]; // ������ ���������� ������
	int end = 4; // ������ �������� ������� = 5 - 1
	ver[0] = end + 1; // ��������� ������� - �������� �������
	int k = 1; // ������ ���������� �������
	int weight = minDistance[end]; // ��� �������� �������

	while (end > 0) // ���� �� ����� �� ��������� �������
	{
		for (int i = 0; i < SIZE; i++) // ������������� ��� �������
			if (transferMatrix[end][i] != 0)   // ���� ����� ����
			{
				int temp = weight - transferMatrix[end][i]; // ���������� ��� ���� �� ���������� �������
				if (temp == minDistance[i]) // ���� ��� ������ � ������������
				{                 // ������ �� ���� ������� � ��� �������
					weight = temp; // ��������� ����� ���
					end = i;       // ��������� ���������� �������
					ver[k] = i + 1; // � ���������� �� � ������
					k++;
				}
			}
	}
	// ����� ���� (��������� ������� ��������� � ����� ������� �� k ���������)
	printf("\n����� ����������� ����\n");
	for (int i = k - 1; i >= 0; i--)
		printf("%3d ", ver[i]);
	getchar(); getchar();
	return 0;
	
	//// Code for heap testing
	//const size_t size = 7;
	//BinaryHeap heap(size);
	//int k;
	////system("chcp 1251");
	////system("cls");
	//vector<int> elements = { 25, 14, 18, 11, 31, 37, 15 };
	//for each (int var in elements)
	//{
	//	//cout << "������� ������� " << i + 1 << ": ";
	//	//cin >> k;
	//	heap.addelem(var);
	//}
	//cout << heap.printAsHeap();
	//cout << endl;
	//cout << heap.printAsArray();
	//cout << endl << "������������ ������� : " << heap.getmax();
	//cout << endl << "����� ���� : " << endl;
	//cout << heap.printAsHeap();
	//cout << endl;
	//cout << heap.printAsArray();
	//cout << endl << "������������ ������� : " << heap.getmax();
	//cout << endl << "����� ���� : " << endl;
	//cout << heap.printAsHeap();
	//cout << endl;
	//cout << heap.printAsArray();
	//cin.get(); cin.get();
	//return 0;
}


// DijkstraAndBinaryHeap.cpp: определяет точку входа для консольного приложения.
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
	int transferMatrix[SIZE][SIZE]; // матрица связей
	int minDistance[SIZE]; // минимальное расстояние
	int markedVertexes[SIZE]; // посещенные вершины
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

	//// Инициализация матрицы связей
	//for (int i = 0; i < SIZE; i++)
	//{
	//	transferMatrix[i][i] = 0;
	//	for (int j = i + 1; j < SIZE; j++) {
	//		printf("Введите расстояние %d - %d: ", i + 1, j + 1);
	//		scanf_s("%d", &temp);
	//		transferMatrix[i][j] = temp;
	//		transferMatrix[j][i] = temp;
	//	}
	//}
	
	cout << graph.print() << endl;
	//// Вывод матрицы связей
	//for (int i = 0; i < SIZE; i++)
	//{
	//	for (int j = 0; j < SIZE; j++)
	//		printf("%5d ", transferMatrix[i][j]);
	//	printf("\n");
	//}

	
	// Вывод кратчайших расстояний до вершин
	printf("\nКратчайшие расстояния до вершин: \n");
	for (int i = 0; i < SIZE; i++)
		printf("%5d ", minDistance[i]);

	// Восстановление пути
	int ver[SIZE]; // массив посещенных вершин
	int end = 4; // индекс конечной вершины = 5 - 1
	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = minDistance[end]; // вес конечной вершины

	while (end > 0) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < SIZE; i++) // просматриваем все вершины
			if (transferMatrix[end][i] != 0)   // если связь есть
			{
				int temp = weight - transferMatrix[end][i]; // определяем вес пути из предыдущей вершины
				if (temp == minDistance[i]) // если вес совпал с рассчитанным
				{                 // значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					end = i;       // сохраняем предыдущую вершину
					ver[k] = i + 1; // и записываем ее в массив
					k++;
				}
			}
	}
	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	printf("\nВывод кратчайшего пути\n");
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
	//	//cout << "Введите элемент " << i + 1 << ": ";
	//	//cin >> k;
	//	heap.addelem(var);
	//}
	//cout << heap.printAsHeap();
	//cout << endl;
	//cout << heap.printAsArray();
	//cout << endl << "Максимальный элемент : " << heap.getmax();
	//cout << endl << "Новая куча : " << endl;
	//cout << heap.printAsHeap();
	//cout << endl;
	//cout << heap.printAsArray();
	//cout << endl << "Максимальный элемент : " << heap.getmax();
	//cout << endl << "Новая куча : " << endl;
	//cout << heap.printAsHeap();
	//cout << endl;
	//cout << heap.printAsArray();
	//cin.get(); cin.get();
	//return 0;
}


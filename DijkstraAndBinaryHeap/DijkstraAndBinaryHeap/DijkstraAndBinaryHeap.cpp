// DijkstraAndBinaryHeap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"

#include "MyGraph.h"

#include <locale>
#include "DijkstraAndBinaryHeap.h"

using namespace std;

const int INF = 1000000000;

int main() {
	// Граф взят отсюда https://prog-cpp.ru/deikstra/
	setlocale(LC_ALL, "Russian");
	const size_t SIZE = 6;

	MyGraph graph = MyGraph(SIZE);
	graph.addBidirectionalPath(0, 1, 7);
	graph.addBidirectionalPath(0, 2, 9);
	graph.addBidirectionalPath(0, 5, 14);
	graph.addBidirectionalPath(1, 2, 10);
	graph.addBidirectionalPath(1, 3, 15);
	graph.addBidirectionalPath(2, 3, 11);
	graph.addBidirectionalPath(2, 5, 2);
	graph.addBidirectionalPath(3, 4, 6);
	graph.addBidirectionalPath(4, 5, 9);
	
	cout << graph.print() << endl;

	Dijkstra d = Dijkstra();
	cout << d.findMinPath(0, 5, graph) << endl;
	cout << d.findMinPath(5, 0, graph) << endl;
	cout << d.findMinPath(0, 4, graph) << endl;

	////////////////////////////////////////////////
	// Есть подозрения что элементы могут выстроиться в дереве не так как нужно
	BinaryHeap<int> heap = BinaryHeap<int>();
	heap.addElement(3);
	heap.addElement(6);
	heap.addElement(4);
	heap.addElement(8);
	heap.addElement(9);
	heap.addElement(12);
	heap.addElement(7);
	heap.addElement(11);
	heap.addElement(9);
	cout << printAsHeap(heap.heapContent) << endl;

	for (size_t i = 0; i < 9; i++)
	{
		cout << "Get min" << heap.getAndDeleteMin() << endl;
		cout << printAsHeap(heap.heapContent) << endl;
	}

	cout << "Test binary heap with pairs<distance, index>" << endl;


	return 0;
}


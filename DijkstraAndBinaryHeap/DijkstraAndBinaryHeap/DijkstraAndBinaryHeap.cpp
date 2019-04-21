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

void testReplace(const size_t index, const size_t value, BinaryHeap<int>& heap) {
	cout << "Test BinaryHeap.replaceElement param: index=" << index << " value=" << value << endl;
	heap.replaceElement(index, value);
	cout << printAsHeap(heap.heapContent) << endl;
}

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

	cout << "Test BinaryHeap.replaceElement" << endl;
	heap.addElement(3);
	heap.addElement(6);
	heap.addElement(4);

	testReplace(0, 4, heap);
	testReplace(0, 7, heap);
	testReplace(2, 2, heap);
	testReplace(1, 21, heap);

	heap.addElement(8);
	heap.addElement(9);
	heap.addElement(12);
	heap.addElement(11);
	cout << printAsHeap(heap.heapContent) << endl;
	testReplace(4, 221, heap);
	testReplace(4, 9, heap);

	testReplace(2, 221, heap);
	
	testReplace(2, 4, heap);
	testReplace(2, 1, heap);
	testReplace(2, 4, heap);
	for (size_t i = 0; i < 7; i++)
	{
		cout << "Get min" << heap.getAndDeleteMin() << endl;
		cout << printAsHeap(heap.heapContent) << endl;
	}

	
	return 0;
}


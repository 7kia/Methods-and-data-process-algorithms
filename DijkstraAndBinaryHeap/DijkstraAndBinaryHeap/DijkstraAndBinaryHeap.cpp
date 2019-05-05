// DijkstraAndBinaryHeap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"

#include "MyGraph.h"

#include <locale>
#include <fstream>
#include "DijkstraAndBinaryHeap.h"

using namespace std;

const int INF = 1000000000;

void testReplace(const size_t index, const size_t value, BinaryHeap<int>& heap) {
	cout << "Test BinaryHeap.replaceElement param: index=" << index << " value=" << value << endl;
	heap.replaceElement(index, static_cast<int>(value));
	cout << printAsHeap(heap.heapContent) << endl;
}
void testFile(const string inputFileName, const string outputFileName) {
	Dijkstra algorithm = Dijkstra();
	const string output = algorithm.findMinPath(inputFileName);
	ofstream outputFile;
	outputFile.open(outputFileName);
	outputFile << output;
	outputFile.close();
}

int main() {
	// Граф взят отсюда https://prog-cpp.ru/deikstra/
	setlocale(LC_ALL, "Russian");
	const size_t SIZE = 6;

	testFile("input.txt", "output.txt");
	testFile("inputReverse.txt", "outputReverse.txt");
	testFile("input_From_1_to_5.txt", "output_From_1_to_5.txt");
	testFile("input_less_road.txt", "output_less_road.txt");
	testFile("input_more_road.txt", "output_more_road.txt");
	//////////////////////////////////////////////////
	//// Есть подозрения что элементы могут выстроиться в дереве не так как нужно
	//BinaryHeap<int> heap = BinaryHeap<int>();
	//heap.addElement(3); 
	//heap.addElement(6); 
	//heap.addElement(4); 
	//heap.addElement(8); cout << printAsHeap(heap.heapContent) << endl;
	//heap.addElement(9); cout << printAsHeap(heap.heapContent) << endl;
	//heap.addElement(12); cout << printAsHeap(heap.heapContent) << endl;
	//heap.addElement(7); cout << printAsHeap(heap.heapContent) << endl;
	//heap.addElement(11); cout << printAsHeap(heap.heapContent) << endl;
	//heap.addElement(9);
	//cout << printAsHeap(heap.heapContent) << endl;
	//
	//for (size_t i = 0; i < 9; i++)
	//{
	//	cout << "Get min" << heap.getAndDeleteMin() << endl;
	//	cout << printAsHeap(heap.heapContent) << endl;
	//}
	//
	//cout << "Test BinaryHeap.replaceElement" << endl;
	//heap.addElement(3);
	//heap.addElement(6);
	//heap.addElement(4);
	//
	//testReplace(0, 4, heap);
	//testReplace(0, 7, heap);
	//testReplace(2, 2, heap);
	//testReplace(1, 21, heap);
	//
	//heap.addElement(8);
	//heap.addElement(9);
	//heap.addElement(12);
	//heap.addElement(11);
	//cout << printAsHeap(heap.heapContent) << endl;
	//testReplace(4, 221, heap);
	//testReplace(4, 9, heap);
	//
	//testReplace(2, 221, heap);
	//
	//testReplace(2, 4, heap);
	//testReplace(2, 1, heap);
	//testReplace(2, 4, heap);
	//for (size_t i = 0; i < 7; i++)
	//{
	//	cout << "Get min" << heap.getAndDeleteMin() << endl;
	//	cout << printAsHeap(heap.heapContent) << endl;
	//}

	
	return 0;
}


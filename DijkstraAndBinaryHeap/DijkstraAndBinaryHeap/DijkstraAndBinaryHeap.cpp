// DijkstraAndBinaryHeap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"

using namespace std;

const int INF = 1000000000;

int main() {
	//int n = 4;
	////... чтение n ...
	//vector < vector < pair<int, int> > > g(n);
	////... чтение графа ...
	//int s = 1; // стартовая вершина

	//vector<int> d(n, INF), p(n);
	//d[s] = 0;
	//vector<char> u(n);
	//for (int i = 0; i < n; ++i) {
	//	int v = -1;
	//	for (int j = 0; j < n; ++j)
	//		if (!u[j] && (v == -1 || d[j] < d[v]))
	//			v = j;
	//	if (d[v] == INF)
	//		break;
	//	u[v] = true;

	//	for (size_t j = 0; j < g[v].size(); ++j) {
	//		int to = g[v][j].first,
	//			len = g[v][j].second;
	//		if (d[v] + len < d[to]) {
	//			d[to] = d[v] + len;
	//			p[to] = v;
	//		}
	//	}
	//}

	////
	//vector<int> path;
	//for (int v = s; v != s; v = p[v])
	//	path.push_back(v);
	//path.push_back(s);
	//reverse(path.begin(), path.end());

	BinaryHeap heap;
	int k;
	//system("chcp 1251");
	//system("cls");
	for (int i = 0; i < 16; i++) {
		cout << "Введите элемент " << i + 1 << ": ";
		cin >> k;
		heap.addelem(k);
	}
	heap.printAsHeap();
	cout << endl;
	heap.printAsArray();
	cout << endl << "Максимальный элемент : " << heap.getmax();
	cout << endl << "Новая куча : " << endl;
	heap.printAsHeap();
	cout << endl;
	heap.printAsArray();
	cout << endl << "Максимальный элемент : " << heap.getmax();
	cout << endl << "Новая куча : " << endl;
	heap.printAsHeap();
	cout << endl;
	heap.printAsArray();
	cin.get(); cin.get();
	return 0;
}


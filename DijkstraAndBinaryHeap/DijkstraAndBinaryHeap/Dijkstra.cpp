#include "stdafx.h"
#include "Dijkstra.h"

void Dijkstra::findMinPath(const size_t from, const size_t to, const MyGraph graph)
{
	int minDistance[SIZE]; // минимальное рассто€ние
	int markedVertexes[SIZE]; // посещенные вершины
	int minindex, min;
							  //»нициализаци€ вершин и рассто€ний
	for (int i = 0; i < SIZE; i++)
	{
		minDistance[i] = 10000;
		markedVertexes[i] = 1;
	}
	minDistance[0] = 0;
	// Ўаг алгоритма
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < SIZE; i++)
		{ // ≈сли вершину ещЄ не обошли и вес меньше min
			if ((markedVertexes[i] == 1) && (minDistance[i] < min))
			{ // ѕереприсваиваем значени€
				min = minDistance[i];
				minindex = i;
			}
		}
		// ƒобавл€ем найденный минимальный вес
		// к текущему весу вершины
		// и сравниваем с текущим минимальным весом вершины
		if (minindex != 10000)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (transferMatrix[minindex][i] > 0)
				{
					temp = min + transferMatrix[minindex][i];
					if (temp < minDistance[i])
					{
						minDistance[i] = temp;
					}
				}
			}
			markedVertexes[minindex] = 0;
		}
	} while (minindex < 10000);
}

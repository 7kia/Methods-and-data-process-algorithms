#include "stdafx.h"
#include "Dijkstra.h"

using namespace std;

string Dijkstra::findMinPath(
	const size_t from, 
	const size_t to,
	const MyGraph graph
)
{
	const size_t size = graph.m_transitionMatrix.size();
	vector<size_t> minDistance = vector<size_t>(size); // минимальное расстояние
	vector<size_t> markedVertexes = vector<size_t>(size);// посещенные вершины
	size_t minindex;
	size_t min;
							  //Инициализация вершин и расстояний
	for (size_t i = 0; i < size; i++)
	{
		minDistance[i] = numeric_limits<size_t>::max();
		markedVertexes[i] = 1;
	}
	minDistance[from] = 0;

	size_t temp;
	// Шаг алгоритма
	do {
		minindex = numeric_limits<size_t>::max();;
		min = numeric_limits<size_t>::max();;
		for (int i = 0; i < size; i++)
		{ // Если вершину ещё не обошли и вес меньше min
			if ((markedVertexes[i] == 1) && (minDistance[i] < min))
			{ // Переприсваиваем значения
				min = minDistance[i];
				minindex = i;
			}
		}
		// Добавляем найденный минимальный вес
		// к текущему весу вершины
		// и сравниваем с текущим минимальным весом вершины
		if (minindex != numeric_limits<size_t>::max())
		{
			for (int i = 0; i < size; i++)
			{
				if (graph.m_transitionMatrix[minindex][i] > 0)
				{
					temp = min + graph.m_transitionMatrix[minindex][i];
					if (temp < minDistance[i])
					{
						minDistance[i] = temp;
					}
				}
			}
			markedVertexes[minindex] = 0;
		}
	} while (minindex < numeric_limits<size_t>::max());

	DataForPath data = recoveryPath(graph, minDistance, from, to);
	return graph.printPath(data);
}

DataForPath Dijkstra::recoveryPath(
	const MyGraph& graph, 
	const vector<size_t>& minDistance,
	const size_t from,
	const size_t to
)
{
	const size_t size = graph.m_transitionMatrix.size();

	vector<size_t> vertexes = vector<size_t>(size); // массив посещенных вершин
	size_t endVertexIndex = to; // индекс конечной вершины = 5 - 1
	vertexes[0] = endVertexIndex; // начальный элемент - конечная вершина
	size_t previousVertexIndex = 1; // индекс предыдущей вершины
	size_t weight = minDistance[endVertexIndex]; // вес конечной вершины

	while (endVertexIndex > 0) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < size; i++) { // просматриваем все вершины
			if (graph.m_transitionMatrix[endVertexIndex][i] != 0)   // если связь есть
			{
				size_t temp = weight - graph.m_transitionMatrix[endVertexIndex][i]; // определяем вес пути из предыдущей вершины
				if (temp == minDistance[i]) // если вес совпал с рассчитанным
				{                 // значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					endVertexIndex = i;       // сохраняем предыдущую вершину
					vertexes[previousVertexIndex] = i + 1; // и записываем ее в массив
					previousVertexIndex++;
				}
			}
		}
	}

	return DataForPath(
		previousVertexIndex, 
		vertexes,
		minDistance[to], 
		from, 
		to
	);
}

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
	vector<size_t> minDistance = vector<size_t>(size); // ����������� ����������
	vector<size_t> markedVertexes = vector<size_t>(size);// ���������� �������
	size_t minIndex;
	size_t min;
	
	//������������� ������ � ����������
	for (size_t i = 0; i < size; i++)
	{
		minDistance[i] = numeric_limits<size_t>::max();
		markedVertexes[i] = 1;
	}
	minDistance[from] = 0;

	size_t temp;
	// ��� ���������
	do {
		minIndex = numeric_limits<size_t>::max();;
		min = numeric_limits<size_t>::max();;
		for (int i = 0; i < size; i++)
		{ // ���� ������� ��� �� ������ � ��� ������ min
			if ((markedVertexes[i] == 1) && (minDistance[i] < min))
			{ // ��������������� ��������
				min = minDistance[i];
				minIndex = i;
			}
		}
		// ��������� ��������� ����������� ���
		// � �������� ���� �������
		// � ���������� � ������� ����������� ����� �������
		if (minIndex != numeric_limits<size_t>::max())
		{
			for (int i = 0; i < size; i++)
			{
				if (graph.m_transitionMatrix[minIndex][i] > 0)
				{
					temp = min + graph.m_transitionMatrix[minIndex][i];
					if (temp < minDistance[i])
					{
						minDistance[i] = temp;
					}
				}
			}
			markedVertexes[minIndex] = 0;
		}
	} while (minIndex < numeric_limits<size_t>::max());

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

	vector<size_t> vertexes = vector<size_t>(size); // ������ ���������� ������
	size_t endVertexIndex = to; // ������ �������� ������� = 5 - 1
	vertexes[0] = endVertexIndex + 1; // ������ + 1 = ����� �������(����� �� 1)
	size_t previousVertexIndex = 1; // ������ ���������� �������
	size_t weight = minDistance[endVertexIndex]; // ��� �������� �������

	while (endVertexIndex != from) // ���� �� ����� �� ��������� �������
	{
		for (int i = 0; i < size; i++) { // ������������� ��� �������
			if (graph.m_transitionMatrix[endVertexIndex][i] != 0)   // ���� ����� ����
			{
				size_t temp = weight - graph.m_transitionMatrix[endVertexIndex][i]; // ���������� ��� ���� �� ���������� �������
				if (temp == minDistance[i]) // ���� ��� ������ � ������������
				{                 // ������ �� ���� ������� � ��� �������
					weight = temp; // ��������� ����� ���
					endVertexIndex = i;       // ��������� ���������� �������
					vertexes[previousVertexIndex] = i + 1; // � ���������� �� � ������
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

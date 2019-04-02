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
	size_t minindex;
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
		minindex = numeric_limits<size_t>::max();;
		min = numeric_limits<size_t>::max();;
		for (int i = 0; i < size; i++)
		{ // ���� ������� ��� �� ������ � ��� ������ min
			if ((markedVertexes[i] == 1) && (minDistance[i] < min))
			{ // ��������������� ��������
				min = minDistance[i];
				minindex = i;
			}
		}
		// ��������� ��������� ����������� ���
		// � �������� ���� �������
		// � ���������� � ������� ����������� ����� �������
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

	vector<size_t> vertexes = vector<size_t>(size); // ������ ���������� ������
	size_t endVertexIndex = to; // ������ �������� ������� = 5 - 1
	vertexes[0] = endVertexIndex; // ��������� ������� - �������� �������
	size_t previousVertexIndex = 1; // ������ ���������� �������
	size_t weight = minDistance[endVertexIndex]; // ��� �������� �������

	while (endVertexIndex > 0) // ���� �� ����� �� ��������� �������
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

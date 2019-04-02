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
	m_minDistance = vector<size_t>(size);
	m_markedVertexes = vector<bool>(size);
	
	initVertexesAndDistances(from, size);

	size_t minIndex;
	size_t min;
	do 
	{
		minIndex = numeric_limits<size_t>::max();;
		min = numeric_limits<size_t>::max();;

		updateMinDistanceForVertexes(size, min, minIndex);
		if (minIndex != numeric_limits<size_t>::max())
		{
			findMinDistanceFromVertex(min, minIndex, graph);
			m_markedVertexes[minIndex] = true;
		}
	} 
	while (minIndex < numeric_limits<size_t>::max());

	DataForPath data = recoveryPath(graph, m_minDistance, from, to);
	return graph.printPath(data);
}


void Dijkstra::updateMinDistanceForVertexes(const size_t size, size_t& min, size_t& minIndex)
{
	for (int i = 0; i < size; i++)
	{
		if ((m_markedVertexes[i] == false) && (m_minDistance[i] < min))
		{
			min = m_minDistance[i];
			minIndex = i;
		}
	}
}

void Dijkstra::initVertexesAndDistances(const size_t from, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		m_minDistance[i] = numeric_limits<size_t>::max();
		m_markedVertexes[i] = false;
	}
	m_minDistance[from] = 0;
}


void Dijkstra::findMinDistanceFromVertex(size_t& min, size_t& minIndex, const MyGraph graph)
{
	const size_t size = graph.m_transitionMatrix.size();
	for (int i = 0; i < size; i++)
	{
		if (graph.m_transitionMatrix[minIndex][i] > 0)
		{
			size_t temp = min + graph.m_transitionMatrix[minIndex][i];
			if (temp < m_minDistance[i])
			{
				m_minDistance[i] = temp;
			}
		}
	}
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

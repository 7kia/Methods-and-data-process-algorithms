#include "stdafx.h"
#include "Dijkstra.h"

void Dijkstra::findMinPath(const size_t from, const size_t to, const MyGraph graph)
{
	int minDistance[SIZE]; // ����������� ����������
	int markedVertexes[SIZE]; // ���������� �������
	int minindex, min;
							  //������������� ������ � ����������
	for (int i = 0; i < SIZE; i++)
	{
		minDistance[i] = 10000;
		markedVertexes[i] = 1;
	}
	minDistance[0] = 0;
	// ��� ���������
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < SIZE; i++)
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

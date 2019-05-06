#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"
#include <fstream>
#include <exception>
using namespace std;

std::string Dijkstra::findMinPath(const std::string& inputFileName)
{	
	try
	{
		InputData data = extractDataFrom(inputFileName);
		return findMinPath(data.from, data.to, data.graph);
	}
	catch (exception* e)
	{
		cout << e->what();
		return e->what();
	}
}

InputData Dijkstra::extractDataFrom(const std::string& inputFileName)
{
	ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open()) {
		const string msg = "File " + inputFileName + " not opened";
		throw new exception(msg.c_str());
	}

	size_t nodeAmount;
	size_t roadAmount;
	size_t from;
	size_t to;
	inputFile >> nodeAmount;
	inputFile >> roadAmount;
	inputFile >> from;
	inputFile >> to;

	convertToArrayIndex(from);
	convertToArrayIndex(to);

	MyGraph graph = extractGraphFrom(inputFile, nodeAmount, roadAmount);
	return InputData(from, to, graph);
}

MyGraph Dijkstra::extractGraphFrom(
	std::ifstream & inputFile,
	const size_t nodeAmount,
	const size_t roadAmount
)
{
	MyGraph graph = MyGraph(nodeAmount);
	for (size_t index = 0; index < roadAmount; ++index)
	{
		if (inputFile.eof()) {
			throw new exception("File end");
		}
		size_t from;
		size_t to; 
		size_t distance;

		inputFile >> from;
		inputFile >> to;
		inputFile >> distance;

		convertToArrayIndex(from);
		convertToArrayIndex(to);

		graph.addBidirectionalPath(from, to, distance);
	}
	return graph;
}

void Dijkstra::convertToArrayIndex(size_t & number)
{
	--number;
}

string Dijkstra::findMinPath(
	const size_t from, 
	const size_t to,
	const MyGraph graph
)
{
	const size_t size = graph.m_transitionMatrix.size();	
	initVertexesAndDistances(from, size);

	BinaryHeap<VertexDistance> heap;
	heap.addElement(VertexDistance(from, 0));

	while (!heap.heapContent.empty()) 
	{
		VertexDistance vertex = heap.getAndDeleteMin();
		size_t index = vertex.index;
		size_t currendDistance = vertex.distance;

		bool skipFictitiousPosition = (currendDistance > m_minDistance[index]);
		if (skipFictitiousPosition)
		{
			continue;
		}

		for (size_t j = 0; j < graph.m_transitionMatrix[index].size(); ++j) 
		{
			size_t to = j;
			size_t length = graph.m_transitionMatrix[index][j];
			bool existPath = (length != std::numeric_limits<size_t>::max());
			if (!existPath)
			{
				continue;
			}

			if ((m_minDistance[index] + length) < m_minDistance[to]) {
				m_minDistance[to] = m_minDistance[index] + length;
				heap.addElement(VertexDistance(to, m_minDistance[to]));
			}
		}
	}

	DataForPath data = recoveryPath(graph, m_minDistance, from, to);
	return graph.printPath(data);
}

void Dijkstra::initVertexesAndDistances(const size_t from, const size_t size)
{
	m_minDistance = vector<size_t>(size);
	for (size_t index = 0; index < size; ++index)
	{
		m_minDistance[index] = numeric_limits<size_t>::max();
	}
	m_minDistance[from] = 0;
}


DataForPath Dijkstra::recoveryPath(
	const MyGraph& graph, 
	const vector<size_t>& minDistance,
	const size_t from,
	const size_t to
)
{
	const size_t size = graph.m_transitionMatrix.size();

	vector<size_t> visitedVertexes = vector<size_t>(size);
	size_t endVertexIndex = to;
	visitedVertexes[0] = endVertexIndex + 1;// индекс + 1 = номер вершины(отсчёт с 1)
	size_t previousVertexIndex = 1;
	size_t endVertexWeight = minDistance[endVertexIndex];

	while (endVertexIndex != from)
	{
		for (int i = 0; i < size; i++) {
			bool existTransition = graph.m_transitionMatrix[endVertexIndex][i] != 0;
			if (existTransition)
			{
				size_t weightFromPreviousVertex = endVertexWeight - graph.m_transitionMatrix[endVertexIndex][i];
				bool transitionFromTheVertex = (weightFromPreviousVertex == minDistance[i]);
				if (transitionFromTheVertex) 
				{
					endVertexWeight = weightFromPreviousVertex;
					endVertexIndex = i;
					visitedVertexes[previousVertexIndex] = i + 1;
					previousVertexIndex++;
				}
			}
		}
	}

	return DataForPath(
		previousVertexIndex, 
		visitedVertexes,
		minDistance[to], 
		from, 
		to
	);
}


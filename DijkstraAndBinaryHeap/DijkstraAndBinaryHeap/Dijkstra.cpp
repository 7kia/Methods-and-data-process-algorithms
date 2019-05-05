#include "stdafx.h"
#include "Dijkstra.h"
#include "BinaryHeap.h"
#include <fstream>
#include <exception>
using namespace std;

Dijkstra::Dijkstra()
{
}

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
	BinaryHeap<VertexDistance> heap = BinaryHeap<VertexDistance>();

	bool isChange = false;
	for (int i = 0; i < size; i++)
	{//&& (heap.heapContent[i].distance != m_minDistance[i])
		if (!m_markedVertexes[i] )
		{
			heap.addElement(VertexDistance(i, m_minDistance[i]));
			bool isChange = true;
		}
	}//isChange && (m_minDistance[1] < numeric_limits<size_t>::max())
	
	if (heap.heapContent.size() > 0) {
		VertexDistance minVertex = heap.getAndDeleteMin();
		min = minVertex.distance;
		minIndex = minVertex.index;
	}
}

void Dijkstra::initVertexesAndDistances(const size_t from, const size_t size)
{
	for (size_t index = 0; index < size; ++index)
	{
		if (index == from) {
			m_minDistance.addElement(VertexDistance(from, 0));
		}
		else
		{
			m_minDistance.addElement(VertexDistance(index, numeric_limits<size_t>::max()));
		}
		m_markedVertexes[index] = false;
	}
}


void Dijkstra::findMinDistanceFromVertex(size_t& min, size_t& minIndex, const MyGraph graph)
{
	const size_t size = graph.m_transitionMatrix.size();

	vector<size_t> oldDistance = extractDistance(m_minDistance);
	vector<size_t> currentDistance = vector<size_t>(oldDistance);
	//vector<size_t>(m_minDistance.heapContent.size());
	
	for (int i = 0; i < size; i++)
	{
		if (graph.m_transitionMatrix[minIndex][i] > 0)
		{
			size_t temp = min + graph.m_transitionMatrix[minIndex][i];
			if (temp < currentDistance[i])
			{
				currentDistance[i] = temp;
			}
		}
		if (currentDistance[i] != oldDistance[i]) {
			m_minDistance.replaceElement(i, currentDistance[i]);
		}
		// TODO: попробуй здесь заменять элементы кучи на новые
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

	vector<size_t> visitedVertexes = vector<size_t>(size);
	size_t endVertexIndex = to;
	visitedVertexes[0] = endVertexIndex + 1; // индекс + 1 = номер вершины(отсчёт с 1)
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

bool operator<(const VertexDistance& first, const VertexDistance& second)
{
	return first.distance < second.distance;
}

bool operator<=(const VertexDistance& first, const VertexDistance& second)
{
	return first.distance <= second.distance;
}

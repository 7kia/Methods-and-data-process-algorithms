#pragma once

#include <vector>
#include <utility>// std::pair, std::make_pair
#include <iostream>// std::cout, std::endl

class Dijkstra 
{
	static void findMinPath(const size_t from, const size_t to, const MyGraph graph);
};
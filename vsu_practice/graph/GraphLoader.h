#pragma once
#include <string>
#include "Graph.h"
#include "AdjacencyMatrix.h"

class GraphLoader
{
public:

	static Graph fromFileAsVertexList(std::string filename);
};
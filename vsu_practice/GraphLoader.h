#pragma once
#include <string>
#include "Graph.h"

class GraphLoader
{
public:

	static Graph fromFileAsVertexList(std::string filename);
};
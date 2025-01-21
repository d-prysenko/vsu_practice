#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "GraphRelations.h"
#include "AdjacencyMatrix.h"

// Отключение отладочной информации
//#define NDEBUG

#if defined NDEBUG
#define DEBUG( format, ... )
#else
#define DEBUG( format, ... )   printf(format, __VA_ARGS__ )
#endif



struct VertexTrace
{
	VertexTrace()
		: distance(0), path({})
	{ }

	VertexTrace(float distance, std::vector<std::string> path)
		: distance(distance), path(path)
	{ }

	float distance;
	std::vector<std::string> path;
};


typedef std::map<std::string, VertexTrace> VertexTraces;


class Graph
{
public:	
	Graph();
	Graph(AdjacencyMatrix& mtx);
	
	size_t getOrder();

	float getEccentricity(std::string v);
	float getEccentricity(size_t index);
	float getDiameter();
	float getRadius();
	std::vector<std::string> getPeripheralVertices();
	std::vector<std::string> getCentralVertices();

	void addVertex(std::string vName);
	void addRelation(std::string v1, std::string v2, float weight);

	VertexTraces getDistancesFrom(std::string src);
	VertexTrace getDistanceTo(std::string src, std::string dest);

private:
	
	VertexTraces _dijkstra(std::string src);

	GraphRelations* mGraphRel = new GraphMatrixRelations();

};


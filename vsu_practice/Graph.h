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


struct SearchResult
{
	SearchResult()
	{ }

	SearchResult(std::map<std::string, float> distances, std::map<std::string, std::vector<std::string>> paths)
		: distances(distances), paths(paths)
	{ }

	std::map<std::string, float> distances;
	std::map<std::string, std::vector<std::string>> paths;
};


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

	SearchResult _dijkstra(std::string src, size_t order);
private:
	
	uint8_t error = 0;
	size_t _order = 0;
	float _radius = -1;
	float _diameter = -1;
	std::map<std::string, float> _eccentricities;
	//std::map<std::string, size_t> _vertices;
	//Matrix<float> _adjacencyMatrix;

	GraphRelations* graphRel = new GraphMatrixRelations();


	std::string _getVertexAliasById(size_t src);

};


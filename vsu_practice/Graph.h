#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

//#define NDEBUG

#if defined NDEBUG
#define DEBUG( format, ... )
#else
#define DEBUG( format, ... )   printf(format, __VA_ARGS__ )
#endif

template<class T>
using Matrix = std::vector<std::vector<T>>;

struct Vertex
{
	std::string name;
	float eccentricity;

	Vertex(std::string n)
		: name(n), eccentricity(-1)
	{}
};

class Graph
{
public:
	enum InputType : uint8_t
	{
		VertexList,
		AdjacencyMatrix
	};
	
	Graph();
	Graph(std::string filename, InputType type = VertexList);

	int getOrder();

	float getEccentricity(std::string v);
	float getDiameter();
	std::vector<std::string> getPeripheralVertices();
	float getRadius();
	std::vector<std::string> getCentralVertices();

	void printEccentricity(std::string v);
	void printCentralVertices();
	void printPeripheralVertices();

private:
	
	int _order = 0;
	float _radius = -1;
	float _diameter = -1;
	//std::vector<Vertex> _vertices;
	std::map<std::string, int> _vertices;
	std::vector<Vertex> _vertices2;
	std::vector<float> _eccentricities;
	//std::map<Vertex, float> _eccentricities;
	std::vector<Vertex*> _centralVertices;
	std::vector<Vertex*> _peripheralVertices;

	Matrix<float> _adjacencyMatrix;

	void _readAsVertexList(std::ifstream& fs);
	void _readAsAdjacencyMatrix(std::ifstream& fs);

};


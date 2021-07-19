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

class Graph
{
public:
	enum class InputType : uint8_t
	{
		VertexList,
		AdjacencyMatrix
	};
	
	Graph();
	Graph(std::string filename, InputType type = InputType::VertexList);

	operator bool() const;

	int getOrder();

	float getEccentricity(std::string v);
	float getEccentricity(int index);
	float getDiameter();
	std::vector<std::string> getPeripheralVertices();
	float getRadius();
	std::vector<std::string> getCentralVertices();

	void printEccentricity(std::string v);
	void printCentralVertices();
	void printPeripheralVertices();

private:
	
	uint8_t error = 0;
	int _order = 0;
	float _radius = -1;
	float _diameter = -1;
	std::map<std::string, int> _vertices;
	std::vector<float> _eccentricities;
	Matrix<float> _adjacencyMatrix;

	void _readAsVertexList(std::ifstream& fs);
	void _readAsAdjacencyMatrix(std::ifstream& fs);

};


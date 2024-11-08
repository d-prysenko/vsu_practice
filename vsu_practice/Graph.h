#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

// Отключение отладочной информации
//#define NDEBUG

#if defined NDEBUG
#define DEBUG( format, ... )
#else
#define DEBUG( format, ... )   printf(format, __VA_ARGS__ )
#endif

template<class T>
using Matrix = std::vector<std::vector<T>>;

class AdjacencyMatrix
{
public:

	void addVertex(std::string vName)
	{
		_vertices[vName] = _verticesCount++;
	}

	void initAdjMatrix()
	{
		// Инициализация матрицы смежности
		size_t _order = _vertices.size();
		_adjacencyMatrix.resize(_order);
		for (size_t i = 0; i < _order; i++)
		{
			_adjacencyMatrix[i].resize(_order);
			for (size_t j = 0; j < _order; j++)
				_adjacencyMatrix[i][j] = FLT_MAX;
		}
	}

	void addRelationWeight(std::string v1Name, std::string v2Name, float weight)
	{
		_adjacencyMatrix[_vertices[v1Name]][_vertices[v2Name]] = weight;
	}

	size_t getVerticesCount() {
		return _verticesCount;
	}

	std::map<std::string, size_t> getVertices() {
		return _vertices;
	}

	Matrix<float> getAdjacencyMatrix() {
		return _adjacencyMatrix;
	}

private:
	std::map<std::string, size_t> _vertices;
	size_t _verticesCount = 0;

	Matrix<float> _adjacencyMatrix;
};

class Graph
{
public:	
	Graph();
	Graph(AdjacencyMatrix& mtx);

	operator bool() const;
	
	size_t getOrder();

	float getEccentricity(std::string v);
	float getEccentricity(size_t index);
	float getDiameter();
	float getRadius();
	std::vector<std::string> getPeripheralVertices();
	std::vector<std::string> getCentralVertices();

private:
	
	uint8_t error = 0;
	size_t _order = 0;
	float _radius = -1;
	float _diameter = -1;
	std::vector<float> _eccentricities;
	std::map<std::string, size_t> _vertices;
	Matrix<float> _adjacencyMatrix;


	std::vector<float> _dijkstra(size_t src);
	std::string _getVertexAliasById(size_t src);

};


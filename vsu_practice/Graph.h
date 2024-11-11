#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "GraphRelations.h"

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

class AdjacencyMatrix2
{
public:
	void _addVertexToAdjMtx()
	{
		_adjacencyMatrix.push_back({});

		for (size_t i = 0; i < _verticeId - 1; i++) {
			_adjacencyMatrix.back().push_back(FLT_MAX);
		}

		for (auto& row : _adjacencyMatrix) {
			row.push_back(FLT_MAX);
		}
	}

	void addVertex(std::string vName)
	{
		_vertices[vName] = _verticeId++;

		_addVertexToAdjMtx();
	}

	void removeVertex(std::string vName)
	{
		if (!_vertices.contains(vName)) {
			throw new std::exception(("Error: there is no vertex with alias \"" + vName + "\"!\n").c_str());
		}

		size_t vId = _vertices[vName];

		_vertices.erase(vName);

		_verticeId--;

		// TODO: remove from adjacency matrix

		_adjacencyMatrix.erase(_adjacencyMatrix.begin() + vId);


		for (auto& row : _adjacencyMatrix)
		{
			row.erase(row.begin() + vId);
		}

		for (auto& v : _vertices)
		{
			if (v.second > vId) {
				v.second--;
			}
		}

		// 0 1 a 
		// 3 4 b
		// d e g
		// q w r
	}

	void addRelation(std::string v1, std::string v2, float weight)
	{
		if (!_vertices.contains(v1)) {
			addVertex(v1);
		}

		if (!_vertices.contains(v2)) {
			addVertex(v2);
		}

		_adjacencyMatrix[_vertices[v1]][_vertices[v2]] = weight;
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
		return _vertices.size();
	}

	std::map<std::string, size_t> getVertices() {
		return _vertices;
	}

	Matrix<float> getAdjacencyMatrix() {
		return _adjacencyMatrix;
	}

private:
	std::map<std::string, size_t> _vertices;
	size_t _verticeId = 0;

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
	std::map<std::string, float> _eccentricities;
	//std::map<std::string, size_t> _vertices;
	//Matrix<float> _adjacencyMatrix;

	GraphRelations* graphRel = new GraphMatrixRelations();


	std::vector<float> _dijkstra(size_t src);
	std::string _getVertexAliasById(size_t src);

};


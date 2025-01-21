#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>

template<class T>
using Matrix = std::vector<std::vector<T>>;

//class AdjacencyMatrix
//{
//public:
//
//	void addVertex(std::string vName)
//	{
//		_vertices[vName] = _verticesCount++;
//	}
//
//	void initAdjMatrix()
//	{
//		// Инициализация матрицы смежности
//		size_t _order = _vertices.size();
//		_adjacencyMatrix.resize(_order);
//		for (size_t i = 0; i < _order; i++)
//		{
//			_adjacencyMatrix[i].resize(_order);
//			for (size_t j = 0; j < _order; j++)
//				_adjacencyMatrix[i][j] = FLT_MAX;
//		}
//	}
//
//	void addRelationWeight(std::string v1Name, std::string v2Name, float weight)
//	{
//		_adjacencyMatrix[_vertices[v1Name]][_vertices[v2Name]] = weight;
//	}
//
//	size_t getVerticesCount() {
//		return _verticesCount;
//	}
//
//	std::map<std::string, size_t> getVertices() {
//		return _vertices;
//	}
//
//	Matrix<float> getAdjacencyMatrix() {
//		return _adjacencyMatrix;
//	}
//
//private:
//	std::map<std::string, size_t> _vertices;
//	size_t _verticesCount = 0;
//
//	Matrix<float> _adjacencyMatrix;
//
//};

class AdjacencyMatrix
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

	void addVertexManual(std::string vName)
	{
		_vertices[vName] = _verticeId++;
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

	bool hasRelation(std::string v1Name, std::string v2Name)
	{
		return _adjacencyMatrix[_vertices[v1Name]][_vertices[v2Name]] != FLT_MAX;
	}

	float getRelationWeight(std::string v1Name, std::string v2Name)
	{
		return _adjacencyMatrix[_vertices[v1Name]][_vertices[v2Name]];
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
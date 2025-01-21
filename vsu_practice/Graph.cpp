#include "Graph.h"


Graph::Graph()
{
}

Graph::Graph(AdjacencyMatrix& mtx)
{
	//_order = mtx.getVerticesCount();
	//std::copy(mtx.getVertices().begin(), mtx.getVertices().end(), _vertices);
	//std::copy(mtx.getAdjacencyMatrix().begin(), mtx.getAdjacencyMatrix().end(), _adjacencyMatrix);

	//_vertices = mtx.getVertices();
	//_adjacencyMatrix = mtx.getAdjacencyMatrix();

	// Выделение места под матрицу размером _order * _order
	//Matrix<float> paths(_order);
	//for (int i = 0; i < _order; i++)
	//{
	//	// Вычисление расстояний от вершины i до остальных с помощью алгоримта Дейкстры
	//	paths[i] = _dijkstra(i);
	//}

	//// Поиск расстояния до наиболее удаленной вершины от данной
	//for (int i = 0; i < _order; i++)
	//{
	//	float max = FLT_MIN;
	//	for (int j = 0; j < _order; j++)
	//	{
	//		if (paths[i][j] > max && paths[i][j] != FLT_MAX)
	//			max = paths[i][j];
	//	}
	//	// Максимальное расстояние есть эксцентриситет, добавление в массив
	//	//_eccentricities.push_back(max);
	//}
}

// Возвращает порядок
size_t Graph::getOrder()
{
	return _order;
}

/*
// Возвращает эксцентриситет вершины, заданной символьной меткой
float Graph::getEccentricity(std::string v)
{
	//if (!_vertices.contains(v))
	if (!graphRel->hasVertex(v))
	{
		throw new std::exception(("Error: there is no vertex with alias \"" + v + "\"!\n").c_str());
	}

	return _eccentricities[_vertices[v]];
}

// Возвращает эксцентриситет вершины по порядковому номеру
float Graph::getEccentricity(size_t index)
{
	if (index >= _order)
	{
		throw new std::exception(("Error: there is no vertex with index \"" + std::to_string(index) + "\"!\n").c_str());
	}

	return _eccentricities[index];
}

// Возвращает диаметр
float Graph::getDiameter()
{
	if (_diameter < 0)
		_diameter = *std::max_element(_eccentricities.begin(), _eccentricities.end());

	return _diameter;
}

// Возвращает массив периферийных вершин
std::vector<std::string> Graph::getPeripheralVertices()
{
	std::vector<std::string> res;
	for (int i = 0; i < _eccentricities.size(); i++)
	{
		if (_eccentricities[i] == getDiameter())
		{
			res.push_back(_getVertexAliasById(i));
		}
	}
	return res;
}

// Возвращает радиус
float Graph::getRadius()
{
	if (_radius < 0)
		_radius = std::min_element(_eccentricities.begin(), _eccentricities.end());

	return _radius;
}

// Возвращает центральные вершины
std::vector<std::string> Graph::getCentralVertices()
{
	std::vector<std::string> res;
	for (int i = 0; i < _eccentricities.size(); i++)
	{
		if (_eccentricities[i] == getRadius())
		{
			res.push_back(_getVertexAliasById(i));
		}
	}
	return res;
}
*/
//// Алгоритм Дейкстры, возвращает массив расстояний от вершины src
//std::vector<float> Graph::_dijkstra(size_t src)
//{
//	//bool* visited = new bool[_order];
//	//std::map<std::string, float> D;
//	//std::map<std::string, bool> visited;
//
//	//// Инициализация результирующего массива, на всех вершинах временные метки
//	//for (int i = 0; i < _order; i++)
//	//{
//	//	//D.push_back(_adjacencyMatrix[src][i]);
//	//	//D.push_back(graphRel->getWeight(src, i));
//	//	//D[]
//	//	//visited[i] = false;
//	//}
//
//	//D[src] = 0;
//	//int min_dst_vert_id = 0;
//
//	//for (int t = 0; t < _order; t++)
//	//{
//	//	// Поиск наименьшего расстояния, среди вершин с временными метками
//	//	float min = FLT_MAX;
//	//	for (int j = 0; j < _order; j++)
//	//	{
//	//		if (!visited[j] && D[j] < min)
//	//		{
//	//			min = D[j];
//	//			min_dst_vert_id = j;
//	//		}
//	//	}
//	//	visited[min_dst_vert_id] = true;
//	//	// Обновление расстояний для вершин с временными метками с учетом найденного на предыдущем шаге наименьшего расстояния
//	//	for (int j = 0; j < _order; j++)
//	//	{
//	//		//if (
//	//		//	!visited[j] &&
//	//		//	_adjacencyMatrix[min_dst_vert_id][j] != FLT_MAX &&
//	//		//	D[min_dst_vert_id] != FLT_MAX &&
//	//		//	(D[min_dst_vert_id] + _adjacencyMatrix[min_dst_vert_id][j] < D[j])
//	//		//) {
//	//		//	D[j] = D[min_dst_vert_id] + _adjacencyMatrix[min_dst_vert_id][j];
//	//		//}
//
//	//		if (
//	//			!visited[j] &&
//	//			graphRel->hasRelation(min_dst_vert_id, j) &&
//	//			D[min_dst_vert_id] != FLT_MAX &&
//	//			(D[min_dst_vert_id] + graphRel->getWeight(min_dst_vert_id, j) < D[j])
//	//		) {
//	//			D[j] = D[min_dst_vert_id] + graphRel->getWeight(min_dst_vert_id, j);
//	//		}
//	//	}
//	//}
//
//	//delete[] visited;
//	return std::vector<float>();
//}

std::string Graph::_getVertexAliasById(size_t id)
{
	//return std::find_if(
	//	_vertices.begin(),
	//	_vertices.end(),
	//	[&](std::pair<std::string, size_t> p) { return p.second == id; }
	//)->first;

	return "";
}

void Graph::addVertex(std::string vName)
{
	graphRel->addVertex(vName);
}

void Graph::addRelation(std::string v1, std::string v2, float weight)
{
	graphRel->addRelation(v1, v2, weight);
}


//// Алгоритм Дейкстры, возвращает массив расстояний от вершины src
//std::vector<float> Graph::_dijkstra(size_t src, size_t order)
//{
//	_order = order;
//	bool* visited = new bool[_order];
//	//std::map<std::string, float> D;
//	std::vector<float> D;
//	//std::map<std::string, bool> visited;
//
//	// Инициализация результирующего массива, на всех вершинах временные метки
//	for (int i = 0; i < _order; i++)
//	{
//		D.push_back(graphRel->getWeight(src, i));
//		visited[i] = false;
//		//D.push_back(_adjacencyMatrix[src][i]);
//		//D.push_back(graphRel->getWeight(src, i));
//	}
//
//	D[src] = 0;
//	int closest_vertex = 0;
//
//	for (int t = 0; t < _order; t++)
//	{
//		// Поиск наименьшего расстояния, среди вершин с временными метками
//		float min = FLT_MAX;
//		for (int j = 0; j < _order; j++)
//		{
//			if (!visited[j] && D[j] < min)
//			{
//				min = D[j];
//				closest_vertex = j;
//			}
//		}
//
//		visited[closest_vertex] = true;
//
//		// Обновление расстояний для вершин с временными метками с учетом найденного на предыдущем шаге наименьшего расстояния
//		for (int j = 0; j < _order; j++)
//		{
//			if (
//				!visited[j] &&
//				graphRel->hasRelation(closest_vertex, j) &&
//				D[closest_vertex] != FLT_MAX &&
//				(D[closest_vertex] + graphRel->getWeight(closest_vertex, j) < D[j])
//				) {
//				D[j] = D[closest_vertex] + graphRel->getWeight(closest_vertex, j);
//			}
//		}
//	}
//
//	delete[] visited;
//	return std::vector<float>{};
//}


SearchResult Graph::_dijkstra(std::string src, size_t order)
{
	_order = order;
	std::set<std::string> visited;
	//bool* visited = new bool[_order];
	//std::map<std::string, float> D;
	std::map<std::string, float> D;
	std::map<std::string, std::vector<std::string>> paths;

	//std::map<std::string, bool> visited;

	std::vector<std::string> vertices = graphRel->getVerteces();

	// Инициализация результирующего массива, на всех вершинах временные метки
	for (const std::string& v : vertices)
	{
		D[v] = graphRel->getWeight(src, v);
		if (graphRel->hasRelation(src, v)) {
			paths[v].push_back(v);
		}
		//D.push_back(graphRel->getWeight(src, v));
		//D.push_back(_adjacencyMatrix[src][i]);
		//D.push_back(graphRel->getWeight(src, i));
	}

	D[src] = 0;
	std::string closest_vertex = src;

	for (int t = 0; t < _order; t++)
	{
		// Поиск наименьшего расстояния, среди вершин с временными метками
		float min = FLT_MAX;
		for (const std::string& v : vertices)
		{
			if (!visited.contains(v) && D[v] < min)
			{
				min = D[v];
				closest_vertex = v;
			}
		}

		visited.insert(closest_vertex);

		// Обновление расстояний для вершин с временными метками с учетом найденного на предыдущем шаге наименьшего расстояния
		for (const std::string& v : vertices)
		{
			if (
				!visited.contains(v) &&
				graphRel->hasRelation(closest_vertex, v) &&
				D[closest_vertex] != FLT_MAX &&
				(D[closest_vertex] + graphRel->getWeight(closest_vertex, v) < D[v])
				) {
				D[v] = D[closest_vertex] + graphRel->getWeight(closest_vertex, v);
				paths[v] = paths[closest_vertex];
				paths[v].push_back(v);
			}
		}
	}

	return SearchResult(D, paths);
}


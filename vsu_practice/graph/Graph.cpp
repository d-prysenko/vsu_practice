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
	return mGraphRel->getOrder();
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

void Graph::addVertex(std::string vName)
{
	mGraphRel->addVertex(vName);
}

void Graph::addRelation(std::string v1, std::string v2, float weight)
{
	mGraphRel->addRelation(v1, v2, weight);
}

VertexTraces Graph::getDistancesFrom(std::string src)
{
	return _dijkstra(src);
}

VertexTrace Graph::getDistanceTo(std::string src, std::string dest)
{
	if (!getDistancesFrom(src).contains(dest)) {
		throw new std::exception("graph not contains vertex");
	}

	return getDistancesFrom(src)[dest];
}

VertexTraces Graph::_dijkstra(std::string src)
{
	size_t order = mGraphRel->getOrder();
	std::set<std::string> visited;

	VertexTraces traces;

	std::vector<std::string> vertices = mGraphRel->getVerteces();

	// Инициализация результирующего массива, на всех вершинах временные метки
	for (const std::string& v : vertices)
	{
		traces[v].distance = mGraphRel->getWeight(src, v);

		if (mGraphRel->hasRelation(src, v)) {
			traces[v].path.push_back(v);
		}
	}

	traces[src].distance = 0;
	std::string closest_vertex = src;

	for (int t = 0; t < order; t++)
	{
		// Поиск наименьшего расстояния, среди вершин с временными метками
		float min = FLT_MAX;
		for (const std::string& v : vertices)
		{
			if (!visited.contains(v) && traces[v].distance < min)
			{
				min = traces[v].distance;
				closest_vertex = v;
			}
		}

		visited.insert(closest_vertex);

		// Обновление расстояний для вершин с временными метками с учетом найденного на предыдущем шаге наименьшего расстояния
		for (const std::string& v : vertices)
		{
			if (
				!visited.contains(v) &&
				mGraphRel->hasRelation(closest_vertex, v) &&
				traces[closest_vertex].distance != FLT_MAX &&
				(traces[closest_vertex].distance + mGraphRel->getWeight(closest_vertex, v) < traces[v].distance)
				) {
				traces[v].distance = traces[closest_vertex].distance + mGraphRel->getWeight(closest_vertex, v);

				traces[v].path = traces[closest_vertex].path;
				traces[v].path.push_back(v);
			}
		}
	}

	return traces;
}


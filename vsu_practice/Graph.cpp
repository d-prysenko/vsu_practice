#include "Graph.h"


Graph::Graph()
{
	fprintf(stderr, "Error: do not use default constructor\n");
	error = 2;
}

Graph::Graph(std::string filename, InputType type)
{
	// Открытие файла
	std::ifstream fs(filename);
	if (!fs)
	{
		fprintf(stderr, "Error: cannot open input file \"%s\"!\n", filename.c_str());
		error = 1;
		return;
	}

	//switch (type)
	//{
	//case Graph::InputType::VertexList:
		_readAsVertexList(fs);
	//	break;
	//case Graph::InputType::AdjacencyMatrix:
	//	_readAsAdjacencyMatrix(fs);
	//	break;
	//default:
	//	break;
	//}

	// Закрытие файла
	fs.close();

	// Выделение места под матрицу размером _order * _order
	Matrix<float> paths(_order);
	for (int i = 0; i < _order; i++)
	{
		// Вычисление расстояний от вершины i до остальных с помощью алгоримта Дейкстры
		paths[i] = _dijkstra(i);
	}
	
	// Поиск наибольшего расстояния от данной вершины до какой-то
	for (int i = 0; i < _order; i++)
	{
		float max = FLT_MIN;
		for (int j = 0; j < _order; j++)
		{	
			if (paths[i][j] > max)
				max = paths[i][j];
		}
		// Максимальное расстояние есть эксцентриситет, добавление в массив
		_eccentricities.push_back(max);
	}

#ifndef NDEBUG
	// Печать всех эксцентриситетов
	for (auto it = _vertices.begin(); it != _vertices.end(); ++it)
	{
		printEccentricity(it->first);
	}
#endif
}

Graph::operator bool() const
{
	return error == 0;
}

// Возвращает порядок
int Graph::getOrder()
{
	return _order;
}

// Чтение файла и заполнение матрицы смежности
void Graph::_readAsVertexList(std::ifstream& fs)
{
	std::string line, vertex;
	std::getline(fs, line);
	std::stringstream firstline(line);

	// Чтение первой строки и разледение ее на вершины
	for (int i = 0; std::getline(firstline, vertex, ' '); i++)
		_vertices[vertex] = i;

	// Инициализация матрицы смежности
	_order = _vertices.size();
	_adjacencyMatrix.resize(_order);
	for (int i = 0; i < _order; i++)
	{
		_adjacencyMatrix[i].resize(_order);
		for (int j = 0; j < _order; j++)
			_adjacencyMatrix[i][j] = FLT_MAX;
	}

	// Чтение строк файла с ребрами и весами
	while (std::getline(fs, line))
	{
		std::string src, dest;
		std::stringstream ss(line);
		float weight;
		ss >> src >> dest >> weight;

		// _vertices[s] вернет порядковый индекс вершины с символьной меткой s
		// Заполнение матрицы смежности
		_adjacencyMatrix[_vertices[src]][_vertices[dest]] = weight;
	}

#ifndef NDEBUG
	printf("Вершины графа: ");
	for (auto& v : _vertices)
	{
		printf("%s ", v.first.c_str());
	}
	printf("\n");

	printf("Матрица смежности:\n");
	for (int i = 0; i < _order; i++)
	{
		for (int j = 0; j < _order; j++)
			printf("%.2f\t", (_adjacencyMatrix[i][j] == FLT_MAX) ? 0.0 : _adjacencyMatrix[i][j]);
		printf("\n");
	}
#endif

}


void Graph::_readAsAdjacencyMatrix(std::ifstream& fs)
{
	printf("There is no functionality yet\n");
}

// Возвращает эксцентриситет вершины, заданной символьной меткой
float Graph::getEccentricity(std::string v)
{
	if (_vertices.find(v) == _vertices.end())
	{
		fprintf(stderr, "Error: there is no vertex with alias \"%s\"!\n", v.c_str());
		return 0;
	}

	return _eccentricities[_vertices[v]];
}

// Возвращает эксцентриситет вершины по порядковому номеру
float Graph::getEccentricity(int index)
{
	if (index >= _order)
	{
		fprintf(stderr, "Error: there is no vertex with index %d!\n", index);
		return 0;
	}

	return _eccentricities[index];
}

// Печать радиуса
void Graph::printRadius()
{
	printf("Радиус графа: %.2f\n", getRadius());
}

// Печать эксцентриситета
void Graph::printEccentricity(std::string v)
{
	float e = getEccentricity(v);
	printf("Эксцентриситет %s = ", v.c_str());
	if (e == FLT_MAX) printf("inf\n");
	else printf("%.2f\n", e);
}

// Возвращает диаметр
float Graph::getDiameter()
{
	// Если диаметр не найден, то происходит вычисление и сохранение
	if (_diameter < 0)
		for (float& e : _eccentricities)
		{
			if (e > _diameter)
				_diameter = e;
		}

	// Если диаметр уже был найден, то возвращается записанное значение
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
			// Поиск символьной метки вершины по порядковому номеру
			std::string temp = std::find_if(_vertices.begin(), _vertices.end(),
				[&](std::pair<std::string, int> p) {return p.second == i; })->first;
			res.push_back(temp);
		}
	}
	return res;
}

// Печать диаметра
void Graph::printDiameter()
{
	printf("Диаметр графа: ");
	if (getDiameter() == FLT_MAX)
		printf("inf\n");
	else
		printf("%.2f\n", getDiameter());
}

// Печать периферийных вершин
void Graph::printPeripheralVertices()
{
	auto vv = getPeripheralVertices();
	if (vv.size() == 0)
	{
		printf("Периферийных вершин нет\n");
	}
	else
	{
		printf("Периферийные вершины: ");
		for (auto& v : vv)
		{
			printf("%s ", v.c_str());
		}
		printf("\n");
	}
}

// Возвращает радиус
float Graph::getRadius()
{
	if (_radius < 0)
		_radius = *std::min_element(_eccentricities.begin(), _eccentricities.end());
		
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
			std::string temp = std::find_if(_vertices.begin(), _vertices.end(), [&](std::pair<std::string, int> p) {return p.second == i; })->first;
			res.push_back(temp);
		}
	}
	return res;
}

// Печать центральных вершин
void Graph::printCentralVertices()
{
	auto vv = getCentralVertices();

	if (vv.size() == 0)
	{
		printf("Центральных вершин нет\n");
	}
	else
	{
		printf("Центральные вершины: ");
		for (auto& v : vv)
		{
			printf("%s ", v.c_str());
		}
		printf("\n");
	}
}

// Алгоритм Дейкстры, возвращает массив расстояний от вершины src
std::vector<float> Graph::_dijkstra(int src)
{
	bool* visited = new bool[_order];
	std::vector<float> D;

	// Инициализация результирующего массива, на всех вершинах временные метки
	for (int i = 0; i < _order; i++)
	{
		D.push_back(_adjacencyMatrix[src][i]);
		visited[i] = false;
	}

	D[src] = 0;
	int index = 0, u = 0;
	for (int i = 0; i < _order; i++)
	{
		// Поиск наименьшего расстояния, среди вершин с временными метками
		float min = FLT_MAX;
		for (int j = 0; j < _order; j++)
		{
			if (!visited[j] && D[j] < min)
			{
				min = D[j];
				index = j;
			}
		}
		u = index;
		visited[u] = true;
		// Обновление расстояний для вершин с временными метками с учетом найденного на предыдущем шаге наименьшего расстояния
		for (int j = 0; j < _order; j++)
		{
			if (!visited[j] && _adjacencyMatrix[u][j] != FLT_MAX && D[u] != FLT_MAX && (D[u] + _adjacencyMatrix[u][j] < D[j]))
			{
				D[j] = D[u] + _adjacencyMatrix[u][j];
			}
		}
	}

	delete[] visited;
	return D;
}

#include "Graph.h"


std::vector<float> Dijkstra(Matrix<float>& w, const int n, int st)
{
	bool* visited = new bool[n];
	std::vector<float> D;

	for (int i = 0; i < n; i++)
	{
		D.push_back(w[st][i]);
		visited[i] = false;
	}

	D[st] = 0;
	int index = 0, u = 0;
	for (int i = 0; i < n; i++)
	{
		float min = FLT_MAX;
		for (int j = 0; j < n; j++)
		{
			if (!visited[j] && D[j] < min)
			{
				min = D[j];
				index = j;
			}
		}
		u = index;
		visited[u] = true;
		for (int j = 0; j < n; j++)
		{
			if (!visited[j] && w[u][j] != FLT_MAX && D[u] != FLT_MAX && (D[u] + w[u][j] < D[j]))
			{
				D[j] = D[u] + w[u][j];
			}
		}
	}

	delete[] visited;
	return D;
}


Graph::Graph()
{
	printf("��������� ����������� �� ����������!\n");
}

Graph::Graph(std::string filename, InputType type)
{
	std::ifstream fs(filename);
	if (!fs)
	{
		fprintf(stderr, "Error: cannot open input file \"%s\"!\n", filename.c_str());
		error = 1;
		return;
	}

	switch (type)
	{
	case Graph::InputType::VertexList:
		_readAsVertexList(fs);
		break;
	case Graph::InputType::AdjacencyMatrix:
		_readAsAdjacencyMatrix(fs);
		break;
	default:
		break;
	}

	DEBUG("������� �����: ");
	for (auto& v : _vertices)
	{
		DEBUG("%s ", v.first.c_str());
	}
	DEBUG("\n");

	Matrix<float> paths(_order);
	for (int i = 0; i < _order; i++)
	{
		paths[i] = Dijkstra(_adjacencyMatrix, _order, i);
	}
	
	for (int i = 0; i < _order; i++)
	{
		float max = FLT_MIN;
		for (int j = 0; j < _order; j++)
		{	
			if (paths[j][i] > max && paths[j][i] != FLT_MAX)
				max = paths[j][i];
		}
		_eccentricities.push_back((max != FLT_MIN) ? max : FLT_MAX);
	}

}

Graph::operator bool() const
{
	return error == 0;
}

int Graph::getOrder()
{
	return _order;
}

void Graph::_readAsVertexList(std::ifstream& fs)
{
	std::string line, vertex;
	std::getline(fs, line);
	std::stringstream firstline(line);

	for (int i = 0; std::getline(firstline, vertex, ' '); i++)
		_vertices[vertex] = i;

	_order = _vertices.size();
	_adjacencyMatrix.resize(_order);
	for (int i = 0; i < _order; i++)
	{
		_adjacencyMatrix[i].resize(_order);
		for (int j = 0; j < _order; j++)
			_adjacencyMatrix[i][j] = FLT_MAX;
	}

	while (std::getline(fs, line))
	{
		std::string src, dest;
		float weight;
		std::stringstream ss(line);
		ss >> src >> dest >> weight;
		DEBUG("(%s, %s) weight: %f\n", src.c_str(), dest.c_str(), weight);

		_adjacencyMatrix[_vertices[src]][_vertices[dest]] = weight;
	}

	

#if not defined NDEBUG
	for (int i = 0; i < _order; i++)
	{
		for (int j = 0; j < _order; j++)
			printf("%f\t", (_adjacencyMatrix[i][j] == FLT_MAX) ? 0.0 : _adjacencyMatrix[i][j]);
		printf("\n");
	}
#endif

}


void Graph::_readAsAdjacencyMatrix(std::ifstream& fs)
{
	printf("There is no functionality yet\n");
}

// getting eccentricity for vertex v
float Graph::getEccentricity(std::string v)
{
	if (_vertices.find(v) == _vertices.end())
	{
		fprintf(stderr, "Error: there is no vertex with alias \"%s\"!\n", v.c_str());
		return 0;
	}

	return _eccentricities[_vertices[v]];
}

float Graph::getEccentricity(int index)
{
	if (index >= _order)
	{
		fprintf(stderr, "Error: there is no vertex with index %d!\n", index);
		return 0;
	}

	return _eccentricities[index];
}

void Graph::printEccentricity(std::string v)
{
	float e = getEccentricity(v);
	printf("�������������� %s = ", v.c_str());
	if (e == FLT_MAX) printf("inf\n");
	else printf("%.2f\n", e);
}

float Graph::getDiameter()
{
	if (_diameter < 0)
		for (float& e : _eccentricities)
		{
			if (e > _diameter && e != FLT_MAX)
				_diameter = e;
		}
	
	return _diameter;
}

std::vector<std::string> Graph::getPeripheralVertices()
{
	std::vector<std::string> res;
	for (int i = 0; i < _eccentricities.size(); i++)
	{
		if (_eccentricities[i] == getDiameter())
		{

			std::string temp = std::find_if(_vertices.begin(), _vertices.end(),
				[&](std::pair<std::string, int> p) {return p.second == i; })->first;
			res.push_back(temp);
		}
	}
	return res;
}

void Graph::printPeripheralVertices()
{
	auto vv = getPeripheralVertices();
	if (vv.size() == 0)
	{
		printf("������������ ������ ���\n");
	}
	else
	{
		printf("������������ �������: ");
		for (auto& v : vv)
		{
			printf("%s ", v.c_str());
		}
		printf("\n");
	}
}

float Graph::getRadius()
{
	if (_radius < 0)
		_radius = *std::min_element(_eccentricities.begin(), _eccentricities.end());
		
		return _radius;
}

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

void Graph::printCentralVertices()
{
	auto vv = getCentralVertices();

	if (vv.size() == 0)
	{
		printf("����������� ������ ���\n");
	}
	else
	{
		printf("����������� �������: ");
		for (auto& v : vv)
		{
			printf("%s ", v.c_str());
		}
		printf("\n");
	}
}
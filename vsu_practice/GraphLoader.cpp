#include "GraphLoader.h"

Graph GraphLoader::fromFileAsVertexList(std::string filename)
{
	// Открытие файла
	std::ifstream fs(filename);

	if (!fs)
	{
		throw new std::exception(("Error: cannot open input file '" + filename + "'!\n").c_str());
	}

	AdjacencyMatrix mtx;

	std::string line, vertex;
	std::getline(fs, line);
	std::stringstream firstline(line);

	// Чтение первой строки и разледение ее на вершины
	while (std::getline(firstline, vertex, ' '))
	{
		mtx.addVertexManual(vertex);
	}

	mtx.initAdjMatrix();

	// Чтение строк файла с ребрами и весами
	while (std::getline(fs, line))
	{
		std::string src, dest;
		std::stringstream ss(line);
		float weight;
		ss >> src >> dest >> weight;

		// Заполнение матрицы смежности
		mtx.addRelationWeight(src, dest, weight);
	}

	// Закрытие файла
	fs.close();

	return Graph(mtx);
}

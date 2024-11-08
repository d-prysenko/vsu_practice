// Подключение заголовочных файлов
#include <iostream>
#include "Graph.h"
#include "GraphLoader.h"
#include "GraphPrinter.hpp"

int main()
{
	setlocale(LC_ALL, "ru");

	Graph g;

	try {
		g = GraphLoader::fromFileAsVertexList("graph1.txt");
	}
	catch (std::exception e) {
		fprintf(stderr, e.what());

		system("pause");
		return -1;
	}

	GraphPrinter gp(g);

	gp.printRadius();
	gp.printDiameter();

	gp.printCentralVertices();
	gp.printPeripheralVertices();

	system("pause");
	return 0;
}
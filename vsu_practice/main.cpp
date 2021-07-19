#include <iostream>

#include "Graph.h"

int main()
{
	setlocale(LC_ALL, "ru");

	Graph g("graph3.txt");

	if (g)
	{
		printf("Радиус графа: %f\n", g.getRadius());
		printf("Диаметр графа: %f\n", g.getDiameter());

		g.printCentralVertices();
		g.printPeripheralVertices();
		//__asm int 3;
	}
	else
	{
		fprintf(stderr, "Exiting..\n");
		system("pause");
		return -1;
	}

	system("pause");
	return 0;
}
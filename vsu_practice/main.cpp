#include <iostream>

#include "Graph.h"

int main()
{
	setlocale(LC_ALL, "ru");

	Graph g("graph.txt");

	printf("������ �����: %f\n", g.getRadius());
	printf("������� �����: %f\n", g.getDiameter());

	g.printEccentricity("a");
	g.printEccentricity("b");
	g.printEccentricity("c");
	g.printEccentricity("d");
	g.printEccentricity("e");

	g.printCentralVertices();
	g.printPeripheralVertices();

	system("pause");
	return 0;
}
#pragma once

#include <string>
#include "Graph.h"

class GraphPrinter
{
public:
	GraphPrinter(Graph& g)
		: g(g)
	{}

	/** Печать эксцентриситета */
	void printEccentricity(std::string v)
	{
		float e = g.getEccentricity(v);

		printf("Эксцентриситет %s = ", v.c_str());

		if (e == FLT_MAX)
			printf("inf\n");
		else
			printf("%.2f\n", e);
	}
	
	/** Печать диаметра */
	void printDiameter()
	{
		printf("Диаметр графа: ");

		float d = g.getDiameter();

		if (d == FLT_MAX)
			printf("inf\n");
		else
			printf("%.2f\n", d);
	}

	/** Печать радиуса */
	void printRadius()
	{
		printf("Радиус графа: %.2f\n", g.getRadius());
	}
	
	/** Печать центральных вершин */
	void printCentralVertices()
	{
		auto vv = g.getCentralVertices();

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
	
	/** Печать периферийных вершин */
	void printPeripheralVertices()
	{
		auto vv = g.getPeripheralVertices();

		if (vv.size() == 0)
		{
			printf("Периферийных вершин нет\n");
			return;
		}

		printf("Периферийные вершины: ");
		for (auto& v : vv)
		{
			printf("%s ", v.c_str());
		}
		printf("\n");
	}

private:

	Graph& g;
};
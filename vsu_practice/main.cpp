// Подключение заголовочных файлов
#include <iostream>
#include "Graph.h"

int main()
{
	setlocale(LC_ALL, "ru");

	// Создание экземпляра класса Graph с исходными данными из файла graph.txt
	Graph g("graph1.txt");

	// Проверка, что все открылось и считалось корректно
	if (g)
	{
		printf("Радиус графа: %f\n", g.getRadius());
		printf("Диаметр графа: %f\n", g.getDiameter());

		// Печать центральных и периферийных вершин
		g.printCentralVertices();
		g.printPeripheralVertices();
	}
	else
	{
		// Если в процессе инициализации графа что-то пошло не так,
		// то написать в стандартный поток для ошибок сообщение
		// и вернуть системе код -1, сигнализирующий о неудаче
		fprintf(stderr, "Failure, exiting..\n");
		system("pause");
		return -1;
	}

	system("pause");
	return 0;
}
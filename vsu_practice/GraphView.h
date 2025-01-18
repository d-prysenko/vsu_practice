#pragma once

#include <string>
#include <vector>


const int DEFAULT_RADUIS = 25;
const int SELECTED_RADUIS = 40;

struct Line
{
	float x1, y1, x2, y2;

	Line(float x1, float y1, float x2, float y2)
		: x1(x1), y1(y1), x2(x2), y2(y2)
	{
	}
};

struct Circle
{
	int x, y, radius;
	std::string name;

	Circle(int x, int y, int radius, std::string name = "")
		: x(x), y(y), radius(radius), name(name)
	{
	}
};

Line get_line_between_circles(const Circle& circle1, const Circle& circle2);
float intersect_lower_semicircle_by_line(float r, float k = 1);
float intersect_upper_semicircle_by_line(float r, float k = 1);



struct Edge
{
	const Circle* from;
	const Circle* to;
	Line line;
	float weight;

	Edge(const Circle* from, const Circle* to, const Line line, float weight)
		: from(from), to(to), line(line), weight(weight)
	{
	}

	Edge(const Circle* from, const Circle* to, float weight)
		: from(from), to(to), weight(weight), line(get_line_between_circles(*from, *to))
	{
	}
};

struct LinearFunction
{
	float k, b;

	LinearFunction()
		: k(1), b(0)
	{
	}

	LinearFunction(float k, float b)
		: k(k), b(b)
	{
	}

	float call(float x)
	{
		return k * x + b;
	}

	static LinearFunction fromPoints(float x1, float y1, float x2, float y2)
	{
		float yd = y2 - y1;
		float xd = x2 - x1;

		if (fabs(yd) < 0.0000001) {
			return LinearFunction(0, y1);
		}

		float k = yd / xd;
		float b = y1 - (x1 * yd / xd);

		return LinearFunction(k, b);
	}
};


class GraphView
{
public:
	void addVertexDraft(float x, float y);
	void removeVertexDraft();
	void commitVertexDraft(std::string name);
	void addEdge(float weight);
	void addEdge(size_t from, size_t to, float weight);
	void unselect();
	void unselectAll();
	void select(size_t i, bool single = true);
	void tryToSelectByCoords(float x, float y);
	bool hasEdge(int from, int to);

	const std::vector<Edge>& getEdges();
	const std::vector<Circle>& getCircles();

	const Circle* getSelectedCircle();
	const Circle* getPreviousSelectedCircle();

	bool draft_circle_added = false;
	int selected = -1;
	int previousSelected = -1;

private:
	std::vector<Circle> circles;
	std::vector<Edge> edges;
};













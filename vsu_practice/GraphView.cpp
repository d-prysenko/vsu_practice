#include "GraphView.h"

float intersect_lower_semicircle_by_line(float r, float k)
{
	return (k / fabs(k)) * (-sqrt((r * r) * (k * k + 1))) / ((k * k) + 1);
}

float intersect_upper_semicircle_by_line(float r, float k)
{
	return (k / fabs(k)) * sqrt((r * r) * (k * k + 1)) / ((k * k) + 1);
}


Line get_line_between_circles(const Circle& circle1, const Circle& circle2)
{
	// vertical
	if (fabs(circle1.x - circle2.x) < 0.001)
	{
		if (circle1.y < circle2.y) {
			return Line(circle1.x, circle1.y + circle1.radius, circle2.x, circle2.y - circle2.radius);
		}
		else {
			return Line(circle1.x, circle1.y - circle1.radius, circle2.x, circle2.y + circle2.radius);
		}
	}

	// horizontal
	if (fabs(circle1.y - circle2.y) < 0.001)
	{
		if (circle1.x < circle2.x) {
			return Line(circle1.x + circle1.radius, circle1.y, circle2.x - circle2.radius, circle2.y);
		}
		else {
			return Line(circle1.x - circle1.radius, circle1.y, circle2.x + circle2.radius, circle2.y);
		}
	}

	float x1, x2;

	LinearFunction f = LinearFunction::fromPoints(circle1.x, circle1.y, circle2.x, circle2.y);

	if (circle1.y < circle2.y) {
		x1 = intersect_upper_semicircle_by_line(circle1.radius, f.k);
		x2 = intersect_lower_semicircle_by_line(circle2.radius, f.k);
	}
	else {
		x1 = intersect_lower_semicircle_by_line(circle1.radius, f.k);
		x2 = intersect_upper_semicircle_by_line(circle2.radius, f.k);
	}

	x1 += circle1.x;
	x2 += circle2.x;

	return Line(x1, f.call(x1), x2, f.call(x2));
}

void GraphView::addVertexDraft(float x, float y)
{
	circles.push_back(Circle(x, y, SELECTED_RADUIS));
	draft_circle_added = true;
	selected = circles.size() - 1;
}

void GraphView::removeVertexDraft()
{
	circles.pop_back();
	draft_circle_added = false;
}

void GraphView::commitVertexDraft(std::string name)
{
	draft_circle_added = false;

	circles.back().name = name;
}

void GraphView::addEdge(float weight)
{
	edges.push_back(Edge(&circles[previousSelected], &circles[selected], weight));
}

void GraphView::addEdge(size_t from, size_t to, float weight)
{
	edges.push_back(Edge(&circles[from], &circles[to], weight));
}

void GraphView::unselect()
{
	if (selected < 0) {
		return;
	}

	previousSelected = selected;
	circles[previousSelected].radius = DEFAULT_RADUIS;
	selected = -1;
}

void GraphView::unselectAll()
{
	if (previousSelected >= 0) {
		circles[previousSelected].radius = DEFAULT_RADUIS;
	}

	if (selected >= 0) {
		circles[selected].radius = DEFAULT_RADUIS;
	}

	selected = previousSelected = -1;
}

void GraphView::select(size_t i, bool single)
{
	if (single) {
		unselect();
	}

	previousSelected = selected;
	selected = i;
	circles[selected].radius = SELECTED_RADUIS;
}

void GraphView::tryToSelectByCoords(float x, float y)
{
	previousSelected = selected;
	selected = -1;

	for (int i = 0; i < circles.size() && selected < 0; i++)
	{
		if ((x - circles[i].x) * (x - circles[i].x) + (y - circles[i].y) * (y - circles[i].y) < (circles[i].radius + 20) * (circles[i].radius + 20))
		{
			circles[i].radius = SELECTED_RADUIS;
			selected = i;
		}
	}
}

bool GraphView::hasEdge(int from, int to)
{
	if (from < 0 || to < 0) {
		return false;
	}

	for (const Edge& edge : edges)
	{
		if (edge.from == &circles[from] && edge.to == &circles[to] ||
			edge.from == &circles[to] && edge.to == &circles[from]) {
			return true;
		}
	}

	return false;
}

const std::vector<Edge>& GraphView::getEdges()
{
	return edges;
}

const std::vector<Circle>& GraphView::getCircles()
{
	return circles;
}

const Circle* GraphView::getSelectedCircle()
{
	if (selected < 0) {
		return nullptr;
	}

	return &circles[selected];
}

const Circle* GraphView::getPreviousSelectedCircle()
{
	if (previousSelected < 0) {
		return nullptr;
	}

	return &circles[previousSelected];
}

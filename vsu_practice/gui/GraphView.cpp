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
	mCircleDraft = new Circle(x, y, SELECTED_RADUIS);
}

void GraphView::removeVertexDraft()
{
	delete mCircleDraft;
	mCircleDraft = nullptr;
}

const Circle* GraphView::commitVertexDraft(std::string name)
{
	mCircleDraft->name = name;
	mCircleDraft->radius = DEFAULT_RADUIS;
	mCircles.push_back(mCircleDraft);

	//select(mCircles.size() - 1, false);

	mCircleDraft = nullptr;

	return mCircles.back();
}

bool GraphView::hasVertexDraft()
{
	return mCircleDraft != nullptr;
}

const Circle* GraphView::getVertexDraft()
{
	return mCircleDraft;
}

void GraphView::addEdge(float weight)
{
	mEdges.push_back(Edge(mCircles[previousSelected], mCircles[selected], weight));
}

void GraphView::addEdge(const Circle* from, const Circle* to, float weight)
{
	mEdges.push_back(Edge(from, to, weight));
}

void GraphView::addEdge(size_t from, size_t to, float weight)
{
	mEdges.push_back(Edge(mCircles[from], mCircles[to], weight));
}

void GraphView::unselect()
{
	if (selected < 0) {
		return;
	}

	previousSelected = selected;
	mCircles[previousSelected]->radius = DEFAULT_RADUIS;
	selected = -1;
}

void GraphView::unselectAll()
{
	if (previousSelected >= 0) {
		mCircles[previousSelected]->radius = DEFAULT_RADUIS;
	}

	if (selected >= 0) {
		mCircles[selected]->radius = DEFAULT_RADUIS;
	}

	selected = previousSelected = -1;
}

void GraphView::select(size_t i, bool with_resize)
{
	previousSelected = selected;
	selected = i;

	if (with_resize) {
		mCircles[selected]->radius = SELECTED_RADUIS;
	}
}

int GraphView::getCircleOnCoords(float x, float y)
{
	for (int i = 0; i < mCircles.size(); i++)
	{
		if ((x - mCircles[i]->x) * (x - mCircles[i]->x) + (y - mCircles[i]->y) * (y - mCircles[i]->y) < (mCircles[i]->radius + 20) * (mCircles[i]->radius + 20))
		{
			return i;
		}
	}

	return -1;
}

bool GraphView::hasEdge(int from, int to)
{
	if (from < 0 || to < 0) {
		return false;
	}

	for (const Edge& edge : mEdges)
	{
		if (edge.from == mCircles[from] && edge.to == mCircles[to] ||
			edge.from == mCircles[to] && edge.to == mCircles[from]) {
			return true;
		}
	}

	return false;
}

const std::vector<Edge>& GraphView::getEdges()
{
	return mEdges;
}

const std::vector<Circle*>& GraphView::getCircles()
{
	return mCircles;
}

const Circle* GraphView::getSelectedCircle()
{
	if (selected < 0) {
		return nullptr;
	}

	return mCircles[selected];
}

const Circle* GraphView::getPreviousSelectedCircle()
{
	if (previousSelected < 0) {
		return nullptr;
	}

	return mCircles[previousSelected];
}

bool GraphView::hasCorrectPreviusSelectedCirlce()
{


	if (selected >= 0 && selected == previousSelected) {
		return false;
	}

	if (selected >= 0 && previousSelected < 0) {
		return false;
	}

	return true;
}

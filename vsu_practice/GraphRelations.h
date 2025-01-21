#pragma once

#include <string>
#include <set>

#include "AdjacencyMatrix.h"

class GraphRelations
{
public:
	virtual void addVertex(std::string v1) = 0;
	virtual bool hasVertex(std::string v1) = 0;
	virtual std::vector<std::string> getVerteces() = 0;
	virtual size_t getOrder() = 0;

	virtual void addRelation(std::string v1, std::string v2, float weight) = 0;
	virtual bool hasRelation(std::string v1, std::string v2) = 0;
	virtual bool hasRelation(size_t v1, size_t v2) = 0;

	virtual float getWeight(std::string v1, std::string v2) = 0;
	virtual float getWeight(size_t v1, size_t v2) = 0;
};

class GraphMatrixRelations : public GraphRelations
{
public:
	virtual void addVertex(std::string v1)
	{
		mtx.addVertex(v1);
	}

	virtual bool hasVertex(std::string v1)
	{
		return mtx.getVertices().contains(v1);
	}

	virtual std::vector<std::string> getVerteces()
	{
		std::vector<std::string> vertices;

		for (const auto& v : mtx.getVertices())
		{
			vertices.push_back(v.first);
		}

		return vertices;
	}

	virtual size_t getOrder()
	{
		return mtx.getVerticesCount();
	}

	virtual void addRelation(std::string v1, std::string v2, float weight)
	{
		mtx.addRelation(v1, v2, weight);
	}

	virtual bool hasRelation(std::string v1, std::string v2)
	{
		return mtx.hasRelation(v1, v2);
	}

	virtual bool hasRelation(size_t v1, size_t v2)
	{
		return 0;
	}

	virtual float getWeight(std::string v1, std::string v2)
	{
		return mtx.getRelationWeight(v1, v2);
	}

	virtual float getWeight(size_t v1, size_t v2)
	{
		return 0;
	}

private:
	AdjacencyMatrix mtx;
};

class GraphTreeRelations : public GraphRelations
{
public:
	struct GraphTreeNode
	{
		std::string vName;
		std::vector<std::pair<GraphTreeNode*, float>> neighbours;

		bool contains(std::string vName) {
			return false;
		}

		GraphTreeNode* find(std::string vName) {
			return nullptr;
		}
	};

	std::vector<GraphTreeNode*> trees;

	std::set<std::string> _vertices;

	std::set<GraphTreeNode*> _nodes;

	void _addVertex(std::string vName)
	{
		_vertices.insert(vName);
	}


	void addRelation(std::string v1, std::string v2, float weight)
	{
		if (!_vertices.contains(v1)) {
			_addVertex(v1);
		}

		if (!_vertices.contains(v2)) {
			_addVertex(v2);
		}

		bool treeContainsV1 = false;
		for (int i = 0; i < trees.size() && !treeContainsV1; i++)
		{
			if (trees[i]->contains(v1)) {
				treeContainsV1 = true;
			}
		}

		bool treeContainsV2 = false;
		for (int i = 0; i < trees.size() && !treeContainsV2; i++)
		{
			if (trees[i]->contains(v2)) {
				treeContainsV2 = true;
			}
		}

		GraphTreeNode* n1 = new GraphTreeNode;
		n1->vName = v1;

		GraphTreeNode* n2 = new GraphTreeNode;
		n2->vName = v2;

		n1->neighbours.push_back({ n2, weight });

		if (!treeContainsV1 && !treeContainsV2) {
			trees.push_back(n1);
		}
		else if (treeContainsV1)
		{
			//for (const auto& tree : trees) {
			//	tree.
			//}
		}

	}




	virtual bool hasVertex(std::string v1)
	{
		return _vertices.contains(v1);
	}

	virtual bool hasRelation(std::string v1, std::string v2)
	{
		return 0;
	}

	virtual bool hasRelation(size_t v1, size_t v2)
	{
		return 0;
	}

	virtual float getWeight(std::string v1, std::string v2)
	{
		return 0;
	}

	virtual float getWeight(size_t v1, size_t v2)
	{
		return 0;
	}
};

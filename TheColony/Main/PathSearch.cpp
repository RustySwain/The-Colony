#include "PathSearch.h"
#include "GameController.h"

PathSearch::PathSearch() : priorityQueue(IsGreater)
{
}

PathSearch::~PathSearch()
{
	while (!priorityQueue.empty())
		priorityQueue.pop();

	for each(pair<Tile*, SearchNode*> node in nodes)
	{
		node.second->parent = nullptr;
		node.second->visited = false;
	}
}

vector<XMFLOAT3> PathSearch::AStar(XMFLOAT3 _start, XMFLOAT3 _goal)
{
	vector<XMFLOAT3> completePath;
	XMFLOAT3 startP = GameController::GridSquareFromTerrain(_start);
	XMFLOAT3 goalP = GameController::GridSquareFromTerrain(_goal);

	Tile * start = new Tile();
	start->position = startP;
	Tile * goal = new Tile();
	goal->position = goalP;

	priorityQueue.enqueue(nodes[start]);

	while (!priorityQueue.empty())
	{
		Tile* current = priorityQueue.front()->tile;
		priorityQueue.pop();
		SearchNode * currNode = nodes[current];

		float dist = sqrt(pow(goal->position.x - current->position.x, 2) + pow(goal->position.z - current->position.z, 2));
		if (dist < 1.0f)
		{
			SearchNode *temp = currNode;
			while (temp->parent)
			{
				completePath.push_back(temp->tile->position);
				temp = temp->parent;
			}
			completePath.push_back(goal->position);
			return completePath;
		}

		for (size_t i = 0; i < currNode->edges.size(); ++i)
		{
			SearchNode *successor = currNode->edges[i]->endpoint;
			float tempGivenCost = currNode->givenCost + currNode->edges[i]->cost;

			if (successor->visited == false)
			{
				successor->visited = true;
				successor->parent = currNode;
				successor->givenCost = tempGivenCost;
				successor->cost = sqrt((float)pow(goal->position.x - successor->tile->position.x, 2) + (float)pow(goal->position.y - successor->tile->position.y, 2));
				successor->finalCost = successor->givenCost + (successor->cost * 1.0f);
				priorityQueue.enqueue(successor);
			}
			else if (tempGivenCost < successor->givenCost)
			{
				priorityQueue.remove(successor);
				successor->givenCost = tempGivenCost;
				successor->parent = currNode;
				successor->finalCost = tempGivenCost + (successor->cost * 1.0f);
				priorityQueue.enqueue(successor);
			}
		}
	}

	return completePath;
}

bool PathSearch::IsGreater(SearchNode * const & _lhs, SearchNode * const & _rhs)
{
	return _lhs->finalCost > _rhs->finalCost;
}

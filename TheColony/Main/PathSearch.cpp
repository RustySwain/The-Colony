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
		for (size_t i = 0; i < node.second->edges.size(); ++i)
			delete node.second->edges[i];

		delete node.second;
	}
}

void PathSearch::initialize(TileMap * _tileMap)
{
	tileMap = _tileMap;
	int rows = _tileMap->getRows();
	int columns = _tileMap->getColumns();

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			Tile *currTile = _tileMap->getTile(r, c);
			if (currTile->GetWeight() > 0)
			{
				pair<Tile*, SearchNode*> pair;
				pair.first = currTile;
				pair.second = new SearchNode();
				pair.second->tile = pair.first;
				pair.second->cost = 1;

				Tile* adj[8];
				adj[0] = _tileMap->getTile(r - 1, c); // up
				adj[1] = _tileMap->getTile(r + 1, c); // down
				adj[2] = _tileMap->getTile(r, c - 1); // left
				adj[3] = _tileMap->getTile(r, c + 1); // right
				adj[4] = _tileMap->getTile(r - 1, c - 1); // up left
				adj[5] = _tileMap->getTile(r + 1, c - 1); // down left
				adj[6] = _tileMap->getTile(r - 1, c + 1); // up right
				adj[7] = _tileMap->getTile(r + 1, c + 1); // down right

				for (int i = 0; i < 8; ++i)
				{
					if (adj[i] != nullptr && nodes.find(adj[i]) != nodes.end() && adj[i]->GetWeight() != 0)
					{
						Edge* previousNodeEdge = new Edge();
						Edge* currentNodeEdge = new Edge();

						previousNodeEdge->endpoint = pair.second;
						previousNodeEdge->cost = Estimate(pair.first, adj[i]); //adj[i]->GetWeight();

						currentNodeEdge->endpoint = nodes[adj[i]];
						currentNodeEdge->cost = Estimate(pair.first, adj[i]); // currTile->GetWeight();

						pair.second->edges.push_back(currentNodeEdge);
						nodes[adj[i]]->edges.push_back(previousNodeEdge);
					}
				}

				nodes.insert(pair);
			}
		}
	}
}

vector<XMFLOAT3> PathSearch::AStar(XMFLOAT3 _start, XMFLOAT3 _goal)
{
	// clear nodes
	for each(pair<Tile*, SearchNode*> node in nodes)
	{
		node.second->parent = nullptr;
		node.second->visited = false;
	}

	while (!priorityQueue.empty())
		priorityQueue.pop();

	vector<XMFLOAT3> completePath;
	Tile* start = tileMap->getTile((int)_start.x, (int)_start.z);
	Tile* goal = tileMap->getTile((int)_goal.x, (int)_goal.z);

	priorityQueue.enqueue(nodes[start]);
	nodes[start]->visited = true;
	nodes[start]->parent = nullptr;
	nodes[start]->givenCost = 0;
	nodes[start]->hCost = Estimate(goal, start);
	nodes[start]->finalCost = nodes[start]->givenCost + (nodes[start]->hCost * hWeight);

	while (!priorityQueue.empty())
	{
		Tile* current = priorityQueue.front()->tile;
		priorityQueue.pop();
		SearchNode * currNode = nodes[current];

		float dist = sqrt(pow(goal->GetPosition().x - current->GetPosition().x, 2) + pow(goal->GetPosition().z - current->GetPosition().z, 2));
		if (dist < 1.0f)
		{
			SearchNode *temp = currNode;
			while (temp->parent)
			{
				completePath.push_back(temp->tile->GetPosition());
				temp = temp->parent;
			}
			return completePath;
		}

		if (currNode->cost > 0)
		{
			for (size_t i = 0; i < currNode->edges.size(); ++i)
			{
				SearchNode *successor = currNode->edges[i]->endpoint;
				float tempGivenCost = currNode->givenCost + currNode->edges[i]->cost + currNode->cost;

				if (successor->visited == false)
				{
					successor->visited = true;
					successor->parent = currNode;
					successor->givenCost = tempGivenCost;
					successor->hCost = Estimate(goal, successor->tile);
					successor->finalCost = successor->givenCost + (successor->hCost * hWeight);
					priorityQueue.enqueue(successor);
				}
				else if (tempGivenCost < successor->givenCost)
				{
					priorityQueue.remove(successor);
					successor->givenCost = tempGivenCost;
					successor->parent = currNode;
					successor->finalCost = tempGivenCost + (successor->hCost * hWeight);
					priorityQueue.enqueue(successor);
				}
			}
		}

	}

	return completePath;
}

void PathSearch::ChangeTileCost(Tile * _tile, float _cost)
{
	nodes[_tile]->cost = _cost;
	//for (int i = 0; i < (int)nodes[_tile]->edges.size(); ++i)
	//{
	//	nodes[_tile]->edges[i]->cost = 1;
	//}
}

float PathSearch::Estimate(Tile * _lhs, Tile * _rhs) const
{
	float dist = sqrt((float)pow(_lhs->GetPosition().x - _rhs->GetPosition().x, 2) + (float)pow(_lhs->GetPosition().z - _rhs->GetPosition().z, 2));
	return dist * 0.05f;
}

bool PathSearch::IsGreater(SearchNode * const & _lhs, SearchNode * const & _rhs)
{
	return _lhs->finalCost > _rhs->finalCost;
}

#pragma once
#include <vector>
#include <DirectXMath.h>
#include <unordered_map>
#include "PriorityQueue.h"

using namespace std;
using namespace DirectX;

class PathSearch
{
	struct Edge;
	struct Tile;
	struct SearchNode
	{
		Tile* tile;
		SearchNode *parent;
		vector<Edge*> edges;
		bool visited;
		float cost = 0;
		float givenCost = 0;
		float finalCost = 0;
	};
	struct Edge
	{
		SearchNode* endpoint;
		float cost = 0;
	};
	struct Tile
	{
		XMFLOAT3 position;
	};

	PriorityQueue<SearchNode*> priorityQueue;
	unordered_map<Tile*, SearchNode*> nodes;

	static bool IsGreater(SearchNode * const & _lhs, SearchNode * const & _rhs);

public:
	PathSearch();
	~PathSearch();

	vector<XMFLOAT3> AStar(XMFLOAT3 _start, XMFLOAT3 _goal);
};
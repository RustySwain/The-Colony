#pragma once
#include <vector>
#include <DirectXMath.h>
#include <unordered_map>
#include "PriorityQueue.h"
#include "TileMap.h"

using namespace std;
using namespace DirectX;

class PathSearch
{
	struct Edge;
	struct SearchNode
	{
		Tile *tile;
		SearchNode *parent;
		vector<Edge*> edges;
		bool visited = false;
		float hCost;
		float givenCost;
		float finalCost;
	};
	struct Edge
	{
		SearchNode* endpoint;
		float cost;
	};

	TileMap *tileMap;
	PriorityQueue<SearchNode*> priorityQueue;
	unordered_map<Tile*, SearchNode*> nodes;
	float hWeight = 0.5f;

	static bool IsGreater(SearchNode * const & _lhs, SearchNode * const & _rhs);

public:
	PathSearch();
	~PathSearch();

	void initialize(TileMap * _tileMap);
	vector<XMFLOAT3> AStar(XMFLOAT3 _start, XMFLOAT3 _goal);
	void ChangeTileCost(Tile * _tile, float _cost);
	float Estimate(Tile * _lhs, Tile * _rhs) const;
};
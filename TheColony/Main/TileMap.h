#pragma once
#include <DirectXMath.h>
#include "Tile.h"

using namespace DirectX;
using namespace std;

class TileMap
{
	int rows;
	int columns;
	Tile** tiles;

public:
	TileMap();
	~TileMap();

	void reset();
	void createTileArray(int num_rows, int num_columns);
	void addTile(int row, int column, unsigned char weight);
	Tile* getTile(int row, int column) const;
	int getRows() const { return rows; }
	int getColumns() const { return columns; }
};

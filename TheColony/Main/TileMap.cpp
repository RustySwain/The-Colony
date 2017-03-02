#include "TileMap.h"
#include "GameController.h"

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
	reset();
}

void TileMap::reset()
{
	if (tiles)
	{
		int n = rows * columns;
		rows = columns = 0;

		while (n)
		{
			delete tiles[--n];
			tiles[n] = nullptr;
		}

		delete[] tiles;
		tiles = nullptr;
	}
}

void TileMap::createTileArray(int num_rows, int num_columns)
{
	reset();
	tiles = new Tile*[num_rows * num_columns];
	rows = num_rows;
	columns = num_columns;
}

void TileMap::addTile(int row, int column, unsigned char weight)
{
	tiles[row * columns + column] = new Tile(row, column, weight);
}

Tile * TileMap::getTile(int row, int column) const
{
	if ((0 <= row) && (0 <= column) && (row < rows) && (column < columns))
		return tiles[row * columns + column];
	
	return nullptr;
}

#include "Tile.h"
#include "GameController.h"

Tile::Tile(int r, int c, unsigned int weight) : row(r), column(c), weight(weight)
{
	position = GameController::GridSquareFromTerrain(XMFLOAT3((float)r, 0, (float)c));
}

Tile::~Tile()
{
}
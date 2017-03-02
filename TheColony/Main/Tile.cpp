#include "Tile.h"
#include "GameController.h"

Tile::Tile(int r, int c, unsigned int weight) : row(r), column(c), weight(weight)
{
	XMFLOAT3 temp = GameController::GridSquareFromTerrain(XMFLOAT3((float)r, 0, (float)c));
	temp.x += 0.5f;
	temp.z -= 0.5f;
	position = temp;
}

Tile::~Tile()
{
}
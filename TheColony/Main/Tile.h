#pragma once
#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

class Tile
{
	XMFLOAT3 position;
	int row;
	int column;
	unsigned int weight;

public:
	Tile(int r, int c, unsigned int weight);
	~Tile();

	int getRow() const { return row; }
	int GetColumn() const { return column; }
	XMFLOAT3 GetPosition() const { return position; }
	unsigned int GetWeight() const { return weight; }
	void SetPosition(XMFLOAT3 _pos) { position = _pos; }
};

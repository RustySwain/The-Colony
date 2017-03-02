#include "TerrainFollowing.h"
#include <DirectXMath.h>
#include "GameController.h"
#include "Transform.h"
#include "BoundingVolumeHeirarchy.h"
#include "Collider.h"

using namespace DirectX;

TerrainFollowing::TerrainFollowing()
{
}

TerrainFollowing::~TerrainFollowing()
{
}

void TerrainFollowing::Start()
{
}

void TerrainFollowing::Update()
{
	XMFLOAT3 startPoint, outPosition;
	startPoint = gameObject->GetComponent<Transform>()->GetWorldPosition();
	startPoint.y += 5;
	GameObject::FindFromTag("Terrain")[0]->GetComponent<Collider>()->RayCast(outPosition, startPoint, XMFLOAT3(0, -1, 0));
	gameObject->GetComponent<Transform>()->SetLocalPosition(startPoint.x, outPosition.y, startPoint.z);
}

void TerrainFollowing::OnDelete()
{
}

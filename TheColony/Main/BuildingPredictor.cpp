#include "BuildingPredictor.h"
#include "MeshRenderer.h"
#include "GameController.h"
#include "Transform.h"
#include "Camera.h"
#include "Terrain.h"

BuildingPredictor::BuildingPredictor()
{
}

BuildingPredictor::~BuildingPredictor()
{
}

void BuildingPredictor::Start()
{
	Mesh* mesh = new Mesh();
	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();
	for (unsigned int i = 0; i < 216; i++)
	{
		verts.push_back(Vertex());
		tris.push_back(i);
	}
	gameObject->GetComponent<MeshRenderer>()->GetMesh() = mesh;
	gameObject->GetComponent<MeshRenderer>()->SetDynamic(true);
	gameObject->GetComponent<Transform>()->SetParent(Camera::mainCam->gameObject->GetComponent<Transform>());
}

void BuildingPredictor::Update()
{
}

void BuildingPredictor::OnDelete()
{
}

void BuildingPredictor::AddGreen(XMFLOAT3 _terrainPos)
{
	vector<Vertex>& verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	vector<Vertex> terrainVerts = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	unsigned int width = terrain->GetComponent<Terrain>()->GetWidth();
	unsigned int height = terrain->GetComponent<Terrain>()->GetHeight();

	// bottom left
	XMFLOAT4 v1Pos4 = terrainVerts[_terrainPos.z * width + _terrainPos.x].position;
	XMFLOAT3 v1Pos3(v1Pos4.x, v1Pos4.y, v1Pos4.z);
	v1Pos3 = Camera::mainCam->WorldToScreenSpace(v1Pos3);
	v1Pos4 = XMFLOAT4(v1Pos3.x, v1Pos3.y, v1Pos3.z, 1);

	// top left
	XMFLOAT4 v2Pos4 = terrainVerts[(_terrainPos.z + 1) * width + _terrainPos.x].position;
	XMFLOAT3 v2Pos3(v2Pos4.x, v2Pos4.y, v2Pos4.z);
	v2Pos3 = Camera::mainCam->WorldToScreenSpace(v2Pos3);
	v2Pos4 = XMFLOAT4(v2Pos3.x, v2Pos3.y, v2Pos3.z, 1);

	// bottom right
	XMFLOAT4 v3Pos4 = terrainVerts[(_terrainPos.z + 0) * width + _terrainPos.x + 1].position;
	XMFLOAT3 v3Pos3(v3Pos4.x, v3Pos4.y, v3Pos4.z);
	v3Pos3 = Camera::mainCam->WorldToScreenSpace(v3Pos3);
	v3Pos4 = XMFLOAT4(v3Pos3.x, v3Pos3.y, v3Pos3.z, 1);

	// top right
	XMFLOAT4 v4Pos4 = terrainVerts[(_terrainPos.z + 0) * width + _terrainPos.x + 1].position;
	XMFLOAT3 v4Pos3(v4Pos4.x, v4Pos4.y, v4Pos4.z);
	v4Pos3 = Camera::mainCam->WorldToScreenSpace(v4Pos3);
	v4Pos4 = XMFLOAT4(v4Pos3.x, v4Pos3.y, v4Pos3.z, 1);

	verts[vertsTaken].color = XMFLOAT4(0, 1, 0, 1);
	verts[vertsTaken++].position = v1Pos4;
	verts[vertsTaken].color = XMFLOAT4(0, 1, 0, 1);
	verts[vertsTaken++].position = v2Pos4;
	verts[vertsTaken].color = XMFLOAT4(0, 1, 0, 1);
	verts[vertsTaken++].position = v3Pos4;
	verts[vertsTaken].color = XMFLOAT4(0, 1, 0, 1);
	verts[vertsTaken++].position = v2Pos4;
	verts[vertsTaken].color = XMFLOAT4(0, 1, 0, 1);
	verts[vertsTaken++].position = v4Pos4;
	verts[vertsTaken].color = XMFLOAT4(0, 1, 0, 1);
	verts[vertsTaken++].position = v3Pos4;
}

void BuildingPredictor::AddRed(XMFLOAT3 _terrainPos)
{
}

void BuildingPredictor::Clear()
{
	vertsTaken = 0;
	gameObject->GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(0, 0, 0, 0));
}
#include "BuildingPredictor.h"
#include "MeshRenderer.h"
#include "GameController.h"
#include "Transform.h"
#include "Camera.h"
#include "Terrain.h"

XMFLOAT3 BuildingPredictor::Project(XMFLOAT3 _worldSpace)
{
	XMMATRIX posMat = XMMatrixTranslation(_worldSpace.x, _worldSpace.y, _worldSpace.z);
	posMat = posMat * Camera::mainCam->GetViewMatrix();
	posMat = posMat * Camera::mainCam->GetProjectionMatrix();
	XMVECTOR posVec = posMat.r[3];
	posVec /= posVec.m128_f32[3];
	return XMFLOAT3(posVec.m128_f32[0], posVec.m128_f32[1], posVec.m128_f32[2]);
}

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
	for (unsigned int i = 0; i < 4000; i++)
	{
		verts.push_back(Vertex());
		tris.push_back(i);
	}
	gameObject->GetComponent<MeshRenderer>()->GetMesh() = mesh;
	gameObject->GetComponent<MeshRenderer>()->SetDynamic(true);
	gameObject->GetComponent<MeshRenderer>()->SetType(MeshRenderer::UI);
	//gameObject->GetComponent<Transform>()->SetParent(Camera::mainCam->gameObject->GetComponent<Transform>());
}

void BuildingPredictor::Update()
{
}

void BuildingPredictor::OnDelete()
{
}

void BuildingPredictor::AddColor(XMFLOAT3 _terrainPos, XMFLOAT4 _color)
{
	vector<Vertex>& verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	GameObject* terrain = GameObject::FindFromTag("Terrain")[0];
	vector<Vertex> terrainVerts = terrain->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	unsigned int width = terrain->GetComponent<Terrain>()->GetWidth();

	// bottom left
	XMFLOAT4 v1Pos4 = terrainVerts[(unsigned int)_terrainPos.x * width + (unsigned int)_terrainPos.z].position;
	XMFLOAT3 v1Pos3(v1Pos4.x, v1Pos4.y, v1Pos4.z);
	v1Pos3 = Project(v1Pos3);
	v1Pos4 = XMFLOAT4(v1Pos3.x, v1Pos3.y, 0.001f, 1);

	// top left
	XMFLOAT4 v2Pos4 = terrainVerts[((unsigned int)_terrainPos.x + 1) * width + (unsigned int)_terrainPos.z].position;
	XMFLOAT3 v2Pos3(v2Pos4.x, v2Pos4.y, v2Pos4.z);
	v2Pos3 = Project(v2Pos3);
	v2Pos4 = XMFLOAT4(v2Pos3.x, v2Pos3.y, 0.001f, 1);

	// bottom right
	XMFLOAT4 v3Pos4 = terrainVerts[((unsigned int)_terrainPos.x + 0) * width + (unsigned int)_terrainPos.z + 1].position;
	XMFLOAT3 v3Pos3(v3Pos4.x, v3Pos4.y, v3Pos4.z);
	v3Pos3 = Project(v3Pos3);
	v3Pos4 = XMFLOAT4(v3Pos3.x, v3Pos3.y, 0.001f, 1);

	// top right
	XMFLOAT4 v4Pos4 = terrainVerts[((unsigned int)_terrainPos.x + 1) * width + (unsigned int)_terrainPos.z + 1].position;
	XMFLOAT3 v4Pos3(v4Pos4.x, v4Pos4.y, v4Pos4.z);
	v4Pos3 = Project(v4Pos3);
	v4Pos4 = XMFLOAT4(v4Pos3.x, v4Pos3.y, 0.001f, 1);

	verts[vertsTaken].color = _color;
	verts[vertsTaken++].position = v1Pos4;
	verts[vertsTaken].color = _color;
	verts[vertsTaken++].position = v2Pos4;
	verts[vertsTaken].color = _color;
	verts[vertsTaken++].position = v3Pos4;
	verts[vertsTaken].color = _color;
	verts[vertsTaken++].position = v2Pos4;
	verts[vertsTaken].color = _color;
	verts[vertsTaken++].position = v4Pos4;
	verts[vertsTaken].color = _color;
	verts[vertsTaken++].position = v3Pos4;
}

void BuildingPredictor::Clear()
{
	vector<Vertex>& verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		verts[i].position = XMFLOAT4(0, 0, 0, 1);
	}
	vertsTaken = 0;
	gameObject->GetComponent<MeshRenderer>()->SetMeshColor(XMFLOAT4(0, 0, 0, 0));
}
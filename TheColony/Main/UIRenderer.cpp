#include "UIRenderer.h"
#include "MeshRenderer.h"
#include "Transform.h"

UIRenderer::UIRenderer()
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Start()
{
	gameObject->GetComponent<MeshRenderer>()->SetType(MeshRenderer::UI);
	gameObject->GetComponent<MeshRenderer>()->SetDynamic(true);
	Mesh*& mesh = gameObject->GetComponent<MeshRenderer>()->GetMesh();
	if (!mesh) mesh = new Mesh();
	vector<Vertex>& verts = mesh->GetVertexData();
	vector<unsigned int>& tris = mesh->GetTris();
	for (unsigned int i = 0; i < 4; i++)
		verts.push_back(Vertex());
	for (unsigned int i = 0; i < 6; i++)
		tris.push_back(0);
}

void UIRenderer::Update()
{
}

void UIRenderer::OnDelete()
{
}

void UIRenderer::SetRect(float _top, float _left, float _height, float _width)
{
	top = -_top;
	left = _left;
	height = _height;
	width = _width;
	vector<Vertex>& verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	vector<unsigned int>& tris = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetTris();

	Vertex topLeft;
	topLeft.position.x = left;
	topLeft.position.y = top;
	topLeft.uv.x = 0;
	topLeft.uv.y = 1;

	Vertex bottomLeft;
	bottomLeft.position.x = left;
	bottomLeft.position.y = top - height;
	bottomLeft.uv.x = 0;
	bottomLeft.uv.y = 0;

	Vertex topRight;
	topRight.position.x = left + width;
	topRight.position.y = top;
	topRight.uv.x = 1;
	topRight.uv.y = 1;

	Vertex bottomRight;
	bottomRight.position.x = left + width;
	bottomRight.position.y = top - height;
	bottomRight.uv.x = 1;
	bottomRight.uv.y = 0;

	verts[0] = topLeft;
	verts[1] = bottomLeft;
	verts[2] = topRight;
	verts[3] = bottomRight;

	tris[0] = 1;
	tris[1] = 0;
	tris[2] = 2;
	tris[3] = 1;
	tris[4] = 2;
	tris[5] = 3;
}

XMFLOAT4 UIRenderer::GetRect() const
{
	XMFLOAT3 world = gameObject->GetComponent<Transform>()->GetWorldPosition();
	return XMFLOAT4(top + world.y, left + world.x, height, width);
}
#include "ProgressBar.h"
#include "MeshRenderer.h"
#include "UIRenderer.h"

void ProgressBar::ResetVerts() const
{
	vector<Vertex>& verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	if (mode & HORIZONTAL)
	{
		float offset = width - width * ratio;

		if (mode & POSITIVE)
		{
			verts[2].position.x = originalVerts[2].position.x - offset;
			verts[3].position.x = originalVerts[3].position.x - offset;

			if (mode & FILL)
			{
				verts[2].uv.x = ratio;
				verts[3].uv.x = ratio;
			}
		}
		else
		{
			verts[0].position.x = originalVerts[0].position.x + offset;
			verts[1].position.x = originalVerts[1].position.x + offset;

			if (mode & FILL)
			{
				verts[0].uv.x = 1 - ratio;
				verts[1].uv.x = 1 - ratio;
			}
		}
	}
	else
	{
		float offset = height - height * ratio;

		if (mode & POSITIVE)
		{
			verts[0].position.y = originalVerts[0].position.y - offset;
			verts[2].position.y = originalVerts[2].position.y - offset;

			if (mode & FILL)
			{
				verts[0].uv.y = ratio;
				verts[2].uv.y = ratio;
			}
		}
		else
		{
			verts[1].position.y = originalVerts[1].position.y + offset;
			verts[3].position.y = originalVerts[3].position.y + offset;

			if (mode & FILL)
			{
				verts[1].uv.y = 1 - ratio;
				verts[3].uv.y = 1 - ratio;
			}
		}
	}
}

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Start()
{
	vector<Vertex> verts = gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetVertexData();
	for (unsigned int i = 0; i < 4; i++)
	{
		originalVerts[i] = verts[i];
	}
	XMFLOAT4 rect = gameObject->GetComponent<UIRenderer>()->GetRect();
	height = rect.z;
	width = rect.w;
	gameObject->GetComponent<MeshRenderer>()->SetDynamic(true);
}

void ProgressBar::Update()
{
}

void ProgressBar::OnDelete()
{
}

void ProgressBar::LoadFromFile(fstream& _file)
{
}

void ProgressBar::LoadFromString(string _str)
{
}

string ProgressBar::WriteToString() const
{
	return "";
}
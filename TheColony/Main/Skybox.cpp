#include "Skybox.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}

void Skybox::Start()
{
	gameObject->GetComponent<MeshRenderer>()->SetType(MeshRenderer::SKYBOX);
	gameObject->GetComponent<MeshRenderer>()->LoadFromObj("../Assets/skybox.obj");
	gameObject->GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/skybox.dds");
}

void Skybox::Update()
{
	XMFLOAT3 camPos = Camera::mainCam->gameObject->GetComponent<Transform>()->GetWorldPosition();
	gameObject->GetComponent<Transform>()->SetLocalPosition(camPos.x, camPos.y, camPos.z);
}

void Skybox::OnDelete()
{
}

void Skybox::LoadFromFile(fstream& _file)
{
}

void Skybox::LoadFromString(string _str)
{
}

string Skybox::WriteToString() const
{
	return "";
}
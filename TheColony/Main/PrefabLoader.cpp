#include "PrefabLoader.h"
#include <fstream>
#include <string>
#include "Transform.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Light.h"
#include "Animator.h"

PrefabLoader::PrefabLoader()
{
}

PrefabLoader::~PrefabLoader()
{
}

void PrefabLoader::Start()
{
}

void PrefabLoader::Update()
{
}

void PrefabLoader::OnDelete()
{
}

void PrefabLoader::LoadFromFile(fstream &_file)
{
}

void PrefabLoader::LoadFromString(string _str)
{
}

string PrefabLoader::WriteToString() const
{
	return "";
}

void PrefabLoader::Load(string _path)
{
	fstream inFile;
	inFile.open(_path, ios_base::binary | ios_base::in);

	if (inFile.is_open())
	{
		int id;
		inFile.read((char*)&id, sizeof(int));
		gameObject->SetId(id);

		int nameLength;
		inFile.read((char*)&nameLength, sizeof(int));
		char* name = new char[nameLength + 1];
		inFile.read(name, 1);
		inFile.read(name, nameLength);
		name[nameLength] = 0;
		gameObject->SetName(name);
		delete[] name;

		int tagLength;
		inFile.read((char*)&tagLength, sizeof(int));
		char* tag = new char[tagLength + 1];
		inFile.read(tag, 1);
		inFile.read(tag, tagLength);
		tag[tagLength] = 0;
		gameObject->SetTag(tag);
		delete[] tag;

		bool transparent;
		inFile.read((char*)&transparent, sizeof(bool));
		bool dynamic;
		inFile.read((char*)&dynamic, sizeof(bool));

		int numComponents;
		inFile.read((char*)&numComponents, sizeof(int));
		for (int i = 0; i < numComponents; ++i)
		{
			int component;
			inFile.read((char*)&component, sizeof(int));
			m_Components.push_back(component);
		}

		// Read Components
		for (int i = 0; i < (int)m_Components.size(); ++i)
			LoadComponent(i, inFile);

		inFile.close();
	}
}

void PrefabLoader::LoadComponent(int _component, fstream &_file)
{
	switch (m_Components[_component])
	{
	case _Transform:
		gameObject->AddComponent<Transform>()->LoadFromFile(_file);
		break;
	case _RigidBody:
		//gameObject->AddComponent<RigidBody>()->LoadFromFile(inFile);
		break;
	case _Collider:
		//gameObject->AddComponent<Collider>()->LoadFromFile(inFile);
		break;
	case _Camera:
		gameObject->AddComponent<Camera>()->LoadFromFile(_file);
		break;
	case _GameObjectManager:
		gameObject->AddComponent<GameObjectManager>()->LoadFromFile(_file);
		break;
	case _MeshRenderer:
		gameObject->AddComponent<MeshRenderer>()->LoadFromFile(_file);
		break;
	case _CameraController:
		gameObject->AddComponent<CameraController>()->LoadFromFile(_file);
		break;
	case _Light:
		gameObject->AddComponent<Light>()->LoadFromFile(_file);
		break;
	case _Skybox:
		//gameObject->AddComponent<Skybox>()->LoadFromFile(inFile);
		break;
	case _Animator:
		gameObject->AddComponent<Animator>()->LoadFromFile(_file);
		break;
	case _AudioSource:
		//gameObject->AddComponent<AudioSource>()->LoadFromFile(inFile);
		break;
	default:
		break;
	}
}

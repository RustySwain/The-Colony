#include "PrefabLoader.h"
#include <fstream>

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

void PrefabLoader::LoadFromString(string _str)
{
}

void PrefabLoader::LoadPrefab(string path)
{
	fstream inFile;
	inFile.open(path, ios_base::binary | ios_base::in);

	if(inFile.is_open())
	{
		//string buffer;
		//inFile.getline((char*)buffer.c_str(), '1');

		unsigned int id;
		inFile.read((char*)&id, sizeof(int));
		gameObject->SetId(id);

		int nameLength;
		inFile.read((char*)&nameLength, sizeof(int));
		char* name = new char[nameLength + 1];
		inFile.read(name, nameLength);
		gameObject->SetName(name);
		delete[] name;

		int tagLength;
		inFile.read((char*)&tagLength, sizeof(int));
		char* tag = new char[tagLength + 1];
		inFile.read(tag, tagLength);
		gameObject->SetName(tag);
		delete[] tag;

		bool transparent;
		inFile.read((char*)&transparent, sizeof(bool));
		bool dynamic;
		inFile.read((char*)&dynamic, sizeof(bool));

		inFile.close();
	}
}

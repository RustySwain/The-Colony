#include "GameObject.h"

map<unsigned int, GameObject*> GameObject::gameObjectIds;
map<string, vector<GameObject*>> GameObject::gameObjectTags;

void GameObject::RegisterMe(GameObject* _go)
{
	if (_go->GetId())
	{
		pair<unsigned int, GameObject*> pid;
		pid.first = _go->GetId();
		pid.second = _go;
		gameObjectIds.insert(pid);
	}
	if (_go->GetTag().size())
	{
		auto iter = gameObjectTags.find(_go->GetTag());
		if (iter == gameObjectTags.end())
		{
			pair<string, vector<GameObject*>> ptag;
			ptag.first = _go->GetTag();
			gameObjectTags.insert(ptag);
		}
		gameObjectTags[_go->GetTag()].push_back(_go);
	}
}

void GameObject::UnRegisterMe(GameObject* _go)
{
	if (_go->GetId())
		gameObjectIds.erase(gameObjectIds.find(_go->GetId()));

	if (_go->GetTag().size())
	{
		if (gameObjectTags[_go->GetTag()].size() > 1)
		{
			gameObjectTags[_go->GetTag()].erase(find(gameObjectTags[_go->GetTag()].begin(), gameObjectTags[_go->GetTag()].end(), _go));
		}
		else
		{
			gameObjectTags.erase(gameObjectTags.find(_go->GetTag()));
		}
	}
}

GameObject::GameObject() : id(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
	RegisterMe(this);
	started = true;
	for each(pair<int, vector<Component*>> p in components)
	{
		for each (Component* c in p.second)
		{
			c->Start();
		}
	}
}

void GameObject::Update() const
{
	for each(pair<int, vector<Component*>> p in components)
	{
		for each (Component* c in p.second)
		{
			if (c->GetEnabled())
			{
				c->Update();
			}
		}
	}
}

void GameObject::OnDelete()
{
	if (started)
		UnRegisterMe(this);
	for (auto iter = components.begin(); iter != components.end(); iter++)
	{
		for (unsigned int i = 0; i < iter._Ptr->_Myval.second.size(); i++)
		{
			iter._Ptr->_Myval.second[i]->OnDelete();
			delete iter._Ptr->_Myval.second[i];
		}
		iter._Ptr->_Myval.second.clear();
	}
	components.clear();
}

GameObject* GameObject::FindFromId(unsigned int _id)
{
	auto iter = gameObjectIds.find(_id);
	if (iter == gameObjectIds.end())
		return nullptr;
	return iter._Ptr->_Myval.second;
}

vector<GameObject*> GameObject::FindFromTag(string _str)
{
	auto iter = gameObjectTags.find(_str);
	if (iter == gameObjectTags.end())
		return vector<GameObject*>();
	return iter._Ptr->_Myval.second;
}
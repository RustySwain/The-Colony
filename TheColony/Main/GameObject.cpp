#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
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

GameObject* GameObject::FindFromId(unsigned _id)
{
	return nullptr;
}
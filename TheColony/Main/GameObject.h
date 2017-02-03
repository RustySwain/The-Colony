#pragma once
#include <map>
#include <vector>
#include "assert.h"

using namespace std;

class Component;

class GameObject
{
	unsigned int id;
	string name;
	string tag;

	bool started = false;
	map<unsigned int, vector<Component*>> components;

public:
	GameObject();
	~GameObject();

	void Start();
	void Update() const;
	void OnDelete();

	// Accessors
	const unsigned int GetId() const { return id; }
	const string GetName() const { return name; }
	const string GetTag() const { return tag; }

	// Mutators
	void SetId(unsigned int _id) { id = _id; }
	void SetName(string _name) { name = _name; }
	void SetTag(string _tag) { tag = _tag; }

	template <typename T>
	T* AddComponent();
	template <typename T>
	T* GetComponent();
	template <typename T>
	vector<T*>& GetComponents();
	template <typename T>
	bool RemoveComponent();
};

template <typename T>
T* GameObject::AddComponent()
{
	T* comp = new T();
	// the component needs to have an id of not 0 to make sure it's unique and accessible
	assert(comp->GetId() != 0);
	if (components.find(comp->GetId()) == components.end())
	{
		// GameObject already has component of this type. We add the new one to that vector
		components[comp->GetId()].push_back(comp);
	}
	else
	{
		// GameObject doesn't have this type yet. We create a new vector for it
		pair<int, vector<Component*>> p;
		p.first = comp->GetId();
		components.insert(p);
		components[comp->GetId()].push_back(comp);
	}
	comp->gameObject = this;
	if (started)
		comp->Start();
	return comp;
}

template <typename T>
T* GameObject::GetComponent()
{
	T temp;
	// If GameObject doesn't have any components of this type, return nullptr
	if (components.find(temp.GetId()) == components.end())
		return nullptr;
	// return first component of requested type
	return (T*)components[temp.GetId()][0];
}

template <typename T>
vector<T*>& GameObject::GetComponents()
{
	T temp;
	// If GameObject doesn't have any components of this type, return empty vector
	if (components.find(temp.GetId()) == components.end())
		return (vector<T*>&)components[0];
	// return requested vector
	return (vector<T*>&)components[temp.GetId()];
}

template <typename T>
bool GameObject::RemoveComponent()
{
	T temp;
	// If GameObject doesn't have any components of this type, return false
	if (components.find(temp.GetId()) == components.end())
		return false;
	// Call OnDelete event for component about to be deleted
	vector<T*>& vec = (vector<T*>&)components[temp.GetId()];
	vec[0]->OnDelete();
	delete vec[0];
	// If GameObject only has 1 component of this type, delete vector to increase performance
	if (vec.size() == 1)
		components.erase(temp.GetId());
	else
		vec.erase(vec.begin());
	return true;
}

class Component
{
protected:
	bool enabled = true;

public:
	GameObject* gameObject = nullptr;

	Component() {};
	virtual ~Component() {};

	bool GetEnabled() const { return enabled; };
	void SetEnabled(const bool _enabled) { enabled = _enabled; };

	virtual const unsigned int GetId() const = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void OnDelete() = 0;
	virtual void LoadFromString(string _str) = 0;
	virtual string WriteToString() const = 0;
};

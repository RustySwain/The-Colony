#pragma once
#include "GameObject.h"
#include "GameController.h"

class BuildingABC : public Component
{
	const unsigned int id = 27;

	vector<ITEM_ENUM> inventory;
	unsigned int maxInventory = 500;
	XMFLOAT3 frontDoor;
	vector<GameObject*> inhabitants;
	unsigned int maxInhabitants = 0;
	bool walkable = false;

public:
	// Component
	const unsigned int GetId() const override { return id; }

	virtual XMFLOAT3 GetFrontDoor() const { return frontDoor; }
	virtual void SetFrontDoor(XMFLOAT3 _position) { frontDoor = _position; }

	virtual vector<GameObject*>& GetInhabitants() { return inhabitants; }
	virtual void AddInhabitant(GameObject * _villager) { inhabitants.push_back(_villager); }

	virtual unsigned int MaxInhabitants() const { return maxInhabitants; }
	virtual void MaxInhabitants(const unsigned int _inhabitants) { maxInhabitants = _inhabitants; }

	virtual vector<ITEM_ENUM>& Inventory() { return inventory; }
	virtual unsigned int GetMaxInventory() const { return maxInventory; }
};


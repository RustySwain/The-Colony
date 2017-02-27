#pragma once
#include "GameController.h"

class VillagerController
{
	JOB_ENUM job = No_Job;
	unsigned int health = 100;
	unsigned int hunger = 100;
	// TODO: Add house
	vector<ITEM_ENUM> inventory;
	// TODO: Add spouse
	bool education = false;
	unsigned int age;
	bool isMale;

public:
	VillagerController();
	~VillagerController();

	// TODO: RequestPath(XMFLOAT3 _from, XMFLOAT3 _to);
	void Update();
};


#pragma once
#include "GameController.h"

class VillagerController : public Component
{
	const unsigned int id = 24;

	enum STEP { HOME = 0, TRAVELING, WORKING, SCHOOL, WAITING };

	JOB_ENUM job = No_Job;
	unsigned int health = 100;
	unsigned int hunger = 100;
	GameObject* house;
	vector<ITEM_ENUM> inventory;
	GameObject* spouse;
	bool education = false;
	unsigned int age = 0;
	bool isMale = true;
	bool isWorking = false;
	STEP step = HOME;
	vector<XMFLOAT3> pathToWalk;
	int pathCount = 0;

public:
	VillagerController();
	~VillagerController();

	// Component
	const unsigned int GetId() const override { return id; };
	void Start() override;
	void Update() override;
	void OnDelete() override;

	void RequestPath(XMFLOAT3 _from, XMFLOAT3 _to);
	GameObject * FindJob();
};


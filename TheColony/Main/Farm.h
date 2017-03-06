#pragma once
#include "BuildingABC.h"

class Farm : public BuildingABC
{
	struct Crop
	{
		float currTime = 0;
		float totalTime = 100;
		ITEM_ENUM type;
		float resistance = 0;
		float speed = 1;
		float yield = 10;
		unsigned int health = 100;
		float position[2];
	};

	JOB_ENUM job = FARMER;
	vector<Crop> crops;
	unsigned int maxWorkers = 5;
	vector<GameObject*> currWorkers;
	bool plantable = true;
	bool harvestable = false;

	// Crops Update flag
	bool updateFlag = false;

public:
	Farm() {}
	~Farm() {}

	// Crops GameObjects
	GameObject corn;

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;

	// Accessors
	JOB_ENUM Job() const { return job; }
	unsigned int GetMaxWorkers() const { return maxWorkers; }
	vector<GameObject*> GetCurrWorkers() const { return currWorkers; }

	// Mutators
	bool AddWorker(GameObject * _worker);
};

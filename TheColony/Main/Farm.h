#pragma once
#include "BuildingABC.h"

class Farm : public BuildingABC
{
	JOB_ENUM job = Farmer;
	ITEM_ENUM crop;
	unsigned int maxWorkers = 5;
	vector<GameObject*> currWorkers;
	unsigned int requiredWork;
	unsigned int workDone = 0;

public:
	Farm() {}
	~Farm() {}

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
	void SetCrop(ITEM_ENUM _crop) { crop = _crop; }
};

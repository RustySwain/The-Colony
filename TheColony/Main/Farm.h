#pragma once
#include "BuildingABC.h"

class Farm : public BuildingABC
{
	JOB_ENUM job = No_Job;

public:
	Farm() {}
	~Farm() {}

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;

	// Accessors
	JOB_ENUM Job() const { return job; }

	// Mutators
	void Job(JOB_ENUM _job) { job = _job; }
};

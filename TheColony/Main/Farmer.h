#pragma once
#include "BuildingABC.h"

class Farmer : public BuildingABC
{
	JOB_ENUM job = No_Job;

public:
	Farmer(){}
	~Farmer(){}

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;

	// Accessors
	JOB_ENUM Job() const { return job; }

	// Mutators
	void Job(JOB_ENUM _job) { job = _job; }
};

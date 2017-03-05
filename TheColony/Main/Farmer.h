#pragma once
#include "JobABC.h"

class Farmer : public JobABC
{
	

public:
	Farmer(){}
	~Farmer(){}

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;
};

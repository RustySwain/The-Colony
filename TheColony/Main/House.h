#pragma once
#include "BuildingABC.h"

class House : public BuildingABC
{
public:
	House(){}
	~House(){}

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;
};


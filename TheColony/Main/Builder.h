#pragma once
#include "JobABC.h"

class Builder : public JobABC
{
public:
	Builder();
	~Builder();

	// Component
	void Start() override;
	void Update() override;
	void OnDelete() override;
};

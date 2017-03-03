#pragma once
#include "GameObject.h"

class JobABC : public Component
{
	const unsigned int id = 29;

public:
	JobABC();
	~JobABC();

	// Component
	virtual const unsigned int GetId() const override { return id; };
};

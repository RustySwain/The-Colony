#pragma once
#include "GameObject.h"

// Dependencies
// UIRenderer
class LoadingScreen : public Component
{
	const unsigned int id = 20;
	GameObject text;

public:
	LoadingScreen();
	~LoadingScreen();

	// Component
	virtual const unsigned int GetId() const override { return id; }
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void SetText(string _message);
};

#pragma once
#include "GameObject.h"
#include <functional>

typedef function<void(void)> CallbackFunc;

// Dependencies
// UIRenderer
class Button : public Component
{
	const unsigned int id = 15;
	vector<CallbackFunc*> callbacks;

	bool buttonDown = false;

	void OnClick();

public:
	Button();
	~Button();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void Subscribe(CallbackFunc* _callback);
	bool Unsubscribe(CallbackFunc* _callback);
};

#pragma once
#include "GameObject.h"
#include <functional>

typedef function<void(void)> CallbackFunc;

// Dependencies
// UIRenderer
class Button : public Component
{
	const unsigned int id = 15;
	vector<CallbackFunc> callbacks;

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
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	void Subscribe(CallbackFunc _callback);
	bool Unsubscribe(CallbackFunc _callback);
};

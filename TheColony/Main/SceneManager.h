#pragma once
#include "GameObject.h"
#include "Application.h"
#include "Button.h"

class SceneManager : public Component
{
	const unsigned int id = 18;
	bool flag = false;

	GameObject loadingScreen;

public:
	SceneManager();
	~SceneManager();

	// Component
	const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	template <typename T>
	void LoadScene();
};

template <typename T>
void SceneManager::LoadScene()
{
	gameObject->AddComponent<T>();
	flag = true;
}
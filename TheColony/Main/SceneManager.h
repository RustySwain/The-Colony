#pragma once
#include "GameObject.h"
#include "Application.h"
#include <thread>
#include "MainMenu.h"
#include <mutex>

class SceneManager : public Component
{
	const unsigned int id = 18;
	bool shouldLoad = false;
	bool doneLoading = false;

	GameObject loadingScreen;
	thread loadingThread;
	mutex mtex;

	void InitScene();

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
	shouldLoad = true;
	if (gameObject->GetComponent<T>())
		gameObject->GetComponent<T>()->SetEnabled(false);
	gameObject->AddComponent<T>()->SetEnabled(false);
}

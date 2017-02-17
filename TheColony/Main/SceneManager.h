#pragma once
#include "GameObject.h"
#include "Application.h"

class SceneManager : public Component
{
	const unsigned int id = 18;
	bool flag = false;

public:
	SceneManager();
	~SceneManager();

	// Component
	const unsigned int GetId() const override { return id; };
	void Start() override;
	void Update() override;
	void OnDelete() override;
	void LoadFromFile(fstream &_file) override {}

	template <typename T>
	void LoadScene();
};

template <typename T>
void SceneManager::LoadScene()
{
	//gameObject->RemoveComponent<T>();
	gameObject->AddComponent<T>();
	flag = true;
}
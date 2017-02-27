#pragma once
#include "GameObject.h"

// Dependencies: None
class PrefabLoader : public Component
{
	const unsigned int id = 12;

	enum COMPONENTS { none = 0, _Transform, _RigidBody, _Collider, _Camera, _GameObjectManager, _MeshRenderer, _CameraController, _Light, _Skybox, _Animator, _AudioSource };
	vector<int> m_Components;

public:
	PrefabLoader();
	~PrefabLoader();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void Load(string _path);
	void LoadComponent(int _component, fstream &_file);
};

#pragma once
#include "GameObject.h"
#include "d3d11.h"
#include <DirectXMath.h>

#define ASSERT(bool)

using namespace DirectX;

	// Dependencies
	// Camera
	class CameraController : public Component
	{
		const unsigned int id = 7;
		XMFLOAT2 screenMiddle;
		bool _keyPressed = false;
		bool _thirdPerson = false;
		unsigned int _timer = 0;
		bool _moving = false;
		float elapsed;

	public:
		void ThirdPerson(GameObject obj, float speed);

	public:
		CameraController();
		~CameraController();

		virtual void Start() override;
		virtual void Update() override;
		virtual void OnDelete() override;
		virtual const unsigned int GetId() const override { return id; }
		virtual void LoadFromFile(fstream &_file) override;
		virtual void LoadFromString(string _str) override;
		virtual string WriteToString() const override;

	private:
		float lerp(float point1, float point2, float alpha);
		float xLerp(float mMin, float mMax, float mFactor);
		
	};

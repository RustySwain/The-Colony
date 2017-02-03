#pragma once
class Time
{
	static float deltaTime;

public:
	static void SetDelta(const float& _dt) { deltaTime = _dt; };
	static float Delta() { return deltaTime; };
};

#pragma once
#include "GameObject.h"
#include "Mesh.h"

// Dependencies
// UIRenderer
class ProgressBar : public Component
{
	const unsigned int id = 17;

	float ratio = 1;
	float width = 0, height = 0;
	Vertex originalVerts[4];

	void ResetVerts() const;

public:
	enum Mode { FILL = 1, HORIZONTAL = 2, POSITIVE = 4 };

	ProgressBar();
	~ProgressBar();

	// Component
	virtual const unsigned int GetId() const override { return id; };
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;

	void SetRatio(float _ratio) { ratio = _ratio; ResetVerts(); };
	float GetRatio() const { return ratio; };

	void SetMode(unsigned int _mode) { mode = _mode; ResetVerts(); };
	unsigned int GetMode() const { return mode; };

private:
	unsigned int mode = FILL | HORIZONTAL | POSITIVE;
};

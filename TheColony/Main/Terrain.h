#pragma once
#include "GameObject.h"
#include "NoiseGenerator.h"

// Dependencies
// MeshRenderer
class Terrain : public Component
{
	const unsigned int id = 16;

	NoiseGenerator generator;
	unsigned int width = 0, height = 0;
	unsigned int seed = 0;

	void CreateMesh() const;
	void GenerateHeights();
	void CalculateNormals();
	void GenerateTexture();

public:
	Terrain();
	~Terrain();

	// Component
	virtual void Start() override;
	virtual void Update() override;
	virtual void OnDelete() override;
	virtual const unsigned int GetId() const override { return id; };
	virtual void LoadFromFile(fstream &_file) override;
	virtual void LoadFromString(string _str) override;
	virtual string WriteToString() const override;

	void SetSize(unsigned int _width, unsigned int _height);
	void Seed(unsigned int _seed);
	void Generate();
};

#pragma once
#include <vector>
#include <random>

class NoiseGenerator
{
	unsigned int seed;
	std::vector<unsigned int> sequence;
	std::default_random_engine rand;

	static float Fade(float _t);
	static float Lerp(float _a, float _b, float _t);
	static float Grad(int _hash, float _x, float _y);

public:
	NoiseGenerator(unsigned int _seed = 0);
	~NoiseGenerator();

	void ReSeed(unsigned int _seed);
	float Noise(float _x, float _y);
};

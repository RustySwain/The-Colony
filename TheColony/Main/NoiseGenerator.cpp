#include "NoiseGenerator.h"
#include <numeric>
#include <algorithm>

using namespace std;

float NoiseGenerator::Fade(float _t)
{
	return _t * _t * _t * (_t * (_t * 6 - 15) + 10);
}

float NoiseGenerator::Lerp(float _a, float _b, float _t)
{
	return _a + _t * (_b - _a);
}

float NoiseGenerator::Grad(int _hash, float _x, float _y)
{
	int h = _hash & 15;
	double u = h < 8 ? _x : _y,
		v = h < 4 ? _y : h == 12 || h == 14 ? _x : 0;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

NoiseGenerator::NoiseGenerator(unsigned int _seed) : seed(_seed)
{
	sequence.resize(256);
	rand.seed(seed);
	iota(sequence.begin(), sequence.end(), 0);
	shuffle(sequence.begin(), sequence.end(), rand);
	sequence.insert(sequence.end(), sequence.begin(), sequence.end());
}

NoiseGenerator::~NoiseGenerator()
{
	sequence.clear();
	sequence.resize(256);
	rand.seed(seed);
	iota(sequence.begin(), sequence.end(), 0);
	shuffle(sequence.begin(), sequence.end(), rand);
	sequence.insert(sequence.end(), sequence.begin(), sequence.end());
}

void NoiseGenerator::ReSeed(unsigned _seed)
{
}

float NoiseGenerator::Noise(float _x, float _y)
{
	int x = (int)floor(_x) & 255;
	int y = (int)floor(_y) & 255;

	_x -= floor(_x);
	_y -= floor(_y);

	float u = Fade(_x);
	float v = Fade(_y);

	int A = sequence[x] + y, AA = sequence[A], AB = sequence[A + 1], B = sequence[x + 1] + y, BA = sequence[B], BB = sequence[B + 1];

	float res = Lerp(Lerp(Grad(sequence[AA], x, y), Grad(sequence[BA], x - 1, y), u), Lerp(Grad(sequence[AB], x, y - 1), Grad(sequence[BB], x - 1, y - 1), u), v);
	return (res + 1.0f) / 2.0f;
}
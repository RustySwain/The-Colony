#include "NoiseGenerator.h"
#include <numeric>
#include <algorithm>

using namespace std;

float NoiseGenerator::Fade(float _t)
{
	return _t * _t * _t * (_t * (_t * 6 - 15) + 10);
}

float NoiseGenerator::Lerp(float _t, float _a, float _b)
{
	return _a + _t * (_b - _a);
}

float NoiseGenerator::Grad(int _hash, float _x, float _y, float _z)
{
	int h = _hash & 15;
	float u = h < 8 ? _x : _y, v = h < 4 ? _y : h == 12 || h == 14 ? _x : _z;
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
}

void NoiseGenerator::ReSeed(unsigned _seed)
{
	seed = _seed;
	sequence.clear();
	sequence.resize(256);
	rand.seed(seed);
	iota(sequence.begin(), sequence.end(), 0);
	shuffle(sequence.begin(), sequence.end(), rand);
	sequence.insert(sequence.end(), sequence.begin(), sequence.end());
}

float NoiseGenerator::Noise(float _x, float _y, float _z)
{
	int X = (int)floor(_x) & 255;
	int Y = (int)floor(_y) & 255;
	int Z = (int)floor(_z) & 255;

	_x -= floor(_x);
	_y -= floor(_y);
	_z -= floor(_z);

	float u = Fade(_x);
	float v = Fade(_y);
	float w = Fade(_z);

	int A = sequence[X] + Y;
	int AA = sequence[A] + Z;
	int AB = sequence[A + 1] + Z;
	int B = sequence[X + 1] + Y;
	int BA = sequence[B] + Z;
	int BB = sequence[B + 1] + Z;

	float res = Lerp(w, Lerp(v, Lerp(u, Grad(sequence[AA], _x, _y, _z), Grad(sequence[BA], _x - 1, _y, _z)), Lerp(u, Grad(sequence[AB], _x, _y - 1, _z), Grad(sequence[BB], _x - 1, _y - 1, _z))), Lerp(v, Lerp(u, Grad(sequence[AA + 1], _x, _y, _z - 1), Grad(sequence[BA + 1], _x - 1, _y, _z - 1)), Lerp(u, Grad(sequence[AB + 1], _x, _y - 1, _z - 1), Grad(sequence[BB + 1], _x - 1, _y - 1, _z - 1))));
	return (res + 1.0) / 2.0;
}
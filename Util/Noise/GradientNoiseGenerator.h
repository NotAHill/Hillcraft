#pragma once
#ifndef GRADIENT_NOISE_GENERATOR_H
#define GRADIENT_NOISE_GENERATOR_H

#include <random> // Noise generation
#include <cstdint> // Unsigned 8 byte int
#include <ctime> // Time

// Gradient/Perlin noise generator
class GradientNoiseGenerator
{
public:
	GradientNoiseGenerator(unsigned int _seed = std::time(nullptr));
	void reseed(unsigned int _seed);
	float noise2D(float x, float y);

private:
	// Utility function
	float fade(float t);
	float lerp(float t, float a, float b);
	float clamp(float t, float lower, float upper);

	float invLerp(float t, float a, float b);
	float map(float value, float oldMin, float oldMax, float newMin, float newMax);
	float gradient(int hash, float x, float y, float z);

	uint8_t noiseMap[512];
	unsigned int seed;
};


#endif // !GRADIENT_NOISE_GENERATOR_H



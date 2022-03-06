#pragma once
#ifndef FRACTAL_NOISE_GENERATOR_H
#define FRACTAL_NOISE_GENERATOR_H

#include "GradientNoiseGenerator.h"

class FractalNoiseGenerator
{
public:
	FractalNoiseGenerator(float _scale, int _seed = std::time(nullptr));
	float getNoise(float x, float y);

private:
	GradientNoiseGenerator perlin;

	float scale;
	int seed;
};

#endif // !FRACTAL_NOISE_GENERATOR_H


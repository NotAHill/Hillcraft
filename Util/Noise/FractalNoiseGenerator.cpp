#include "FractalNoiseGenerator.h"
#include <iostream>

FractalNoiseGenerator::FractalNoiseGenerator(float _scale, int _seed) :
	perlin(_seed),
	scale(_scale)
{
	std::cout << "Current Seed: " << _seed << std::endl;
}

float FractalNoiseGenerator::getNoise(float x, float y)
{
	return perlin.noise2D(x / scale, y / scale);
}


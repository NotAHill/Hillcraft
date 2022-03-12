#pragma once
#ifndef FRACTAL_NOISE_GENERATOR_H
#define FRACTAL_NOISE_GENERATOR_H

#include "GradientNoiseGenerator.h"
#include "../../Maths/glm.h"

class FractalNoiseGenerator
{
public:
	FractalNoiseGenerator(float _scale, int _octaves, float _persistance, float _lacunarity, int _seed = std::time(nullptr), glm::vec2 _offset = { 0, 0 });
	float getNoise(float x, float y);
	void reseed(const unsigned int& _seed);
	std::vector<std::vector<float>> generateNoiseMap(int size);

private:
	GradientNoiseGenerator perlin;

	float scale;
	int octaves;
	float persistance;
	float lacunarity;
	std::vector<glm::vec2> octaveOffsets;
};

#endif // !FRACTAL_NOISE_GENERATOR_H


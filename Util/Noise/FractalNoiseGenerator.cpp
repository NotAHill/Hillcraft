#include "FractalNoiseGenerator.h"
#include <iostream>

FractalNoiseGenerator::FractalNoiseGenerator(float _scale, int _octaves, float _persistance, float _lacunarity, int _seed, glm::vec2 _offset) :
	perlin(_seed),
	scale(_scale),
	octaves(_octaves),
	persistance(_persistance),
	lacunarity(_lacunarity)
{
	// Pseudo-random number generator
	std::mt19937 prng(_seed);
	std::uniform_int_distribution<int> nextInt(-1000, 1000);

	octaveOffsets.resize(octaves);
	for (int i = 0; i < octaves; i++)
	{
		float offsetX = (float)nextInt(prng) + _offset.x;
		float offsetY = (float)nextInt(prng) + _offset.y;
		octaveOffsets[i] = { offsetX, offsetY };
	}
}

float FractalNoiseGenerator::getNoise(float x, float y)
{
	float amplitude = 1.0f;
	float frequency = 1.0f;

	float noiseValue = 0.0f;
	float maxNoiseValue = 0.0f;

	for (int i = 0; i < octaves; i++)
	{
		float sampleX = x / scale * frequency + octaveOffsets[i].x;
		float sampleY = y / scale * frequency + octaveOffsets[i].y;

		noiseValue += perlin.noise2D(sampleX, sampleY) * amplitude;
		maxNoiseValue += amplitude;

		amplitude *= persistance;
		frequency *= lacunarity;
	}

	// Normalise the height value
	float result = 2.0f * (noiseValue / maxNoiseValue) - 1.0f;

	return result;
}

std::vector<std::vector<float>> FractalNoiseGenerator::generateNoiseMap(int size)
{
	// Create noise map
	std::vector<std::vector<float>> noiseMap(size, std::vector<float>(size, 0));

	float maxNoiseValue = -INFINITY;
	float minNoiseValue = INFINITY;

	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
		{
			float amplitude = 1.0f;
			float frequency = 1.0f;

			float noiseValue = 0.0f;

			for (int i = 0; i < octaves; i++)
			{
				float sampleX = x / scale * frequency + octaveOffsets[i].x;
				float sampleY = y / scale * frequency + octaveOffsets[i].y;

				noiseValue = perlin.noise2D(sampleX, sampleY) * amplitude;

				amplitude *= persistance;
				frequency *= lacunarity;
			}

			if (noiseValue > maxNoiseValue) maxNoiseValue = noiseValue;
			else if (noiseValue < minNoiseValue) minNoiseValue = noiseValue;
			noiseMap[x][y] = noiseValue;
		}

	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			noiseMap[x][y] = (noiseMap[x][y] - minNoiseValue) / (maxNoiseValue - minNoiseValue);

	return noiseMap;
}


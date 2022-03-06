#include "GradientNoiseGenerator.h"
#include "../Statistics.h"

GradientNoiseGenerator::GradientNoiseGenerator(unsigned int _seed)
{
	reseed(_seed);
}

void GradientNoiseGenerator::reseed(unsigned int _seed)
{
	// Set the seed for the noisemap generation
	seed = _seed;

	// Create map of integers
	for (unsigned i = 0; i < 256; i++)
		noiseMap[i] = i;

	// Permute integers using seed
	std::shuffle(std::begin(noiseMap), std::begin(noiseMap) + 256, std::mt19937(seed));

	// Duplicate integers to prevent buffer oveflow
	for (unsigned i = 0; i < 256; i++)
		noiseMap[256 + i] = noiseMap[i];
}

// Fade/Smootherstep function: 6x^5 -15x^4 + 10x^3
float GradientNoiseGenerator::fade(float t)
{
	t = clamp(t, 0, 1);
	return t * t * t * (t * (t * 6 - 15) + 10);
}

// Linear interpolation between 2 values
float GradientNoiseGenerator::lerp(float t, float a, float b)
{
	//t = clamp(t, a, b);
	return a + t * (b - a);
}

float GradientNoiseGenerator::clamp(float t, float lower, float upper)
{
	if (t < lower) return lower;
	if (t > upper) return upper;
	return t;
}

float GradientNoiseGenerator::map(float value, float oldMin, float oldMax, float newMin, float newMax)
{
	float proportion = (value - oldMin) / (oldMax - oldMin);

	return lerp(value, newMin, newMax);
}

float GradientNoiseGenerator::gradient(int hash, float x, float y, float z)
{
	// Convert last 4 bits of the hash into 12 possible gradients
	int h = hash & 0b1111; // = hash & 15 = hash % 16 = last 4 bits

	// If first bit 1 then set to x otherwise y
	float u = h < 0b1000 ? x : y;

	// if first/second bits 0, set to y
	// if first/second bits 1, set to x
	// else set to z
	float v = h < 0b0100 ? y : h == 0b1100 || h == 0b1110 ? x : z;

	// make u, v negative based on the last 2 bits, then add results
	// adding results is like dot product because gradient components are 1,
	// so results of dot product is adding distance components
	return ((h & 0b0001) == 0 ? u : -u) + ((h & 0b0010) == 0 ? v : -v);
}

float GradientNoiseGenerator::noise2D(float x, float y)
{
	// x & 255 = x % 256 = grid square position
	int gridX = (int)(std::floorf(x)) & 255;
	int gridY = (int)(std::floorf(y)) & 255;

	// Fractional value of x and y
	x -= std::floorf(x);
	y -= std::floorf(y);

	float smoothX = fade(x);
	float smoothY = fade(y);

	auto getHashedValue = [&](int _x, int _y) { return noiseMap[noiseMap[_x] + _y]; };

	uint8_t topLeft = getHashedValue(gridX, gridY);
	uint8_t bottomLeft = getHashedValue(gridX, gridY + 1);
	uint8_t topRight = getHashedValue(gridX + 1, gridY);
	uint8_t bottomRight = getHashedValue(gridX + 1, gridY + 1);

	// Average is calculated between the position and random vectors for the 
	float average = lerp(
		smoothY,
		lerp(
			smoothX,
			gradient(topLeft, x, y, 0),
			gradient(topRight, x - 1, y, 0)
		),
		lerp(
			smoothX,
			gradient(bottomLeft, x, y - 1, 0),
			gradient(bottomRight, x - 1, y - 1, 0)
		)
	);

	// average: [-1, 1] -> [0, 1]
	return average;//map(average, -1, 1, 0, 1);
}



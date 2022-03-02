#pragma once
#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

class NoiseGenerator
{
public:
	NoiseGenerator();

	float random();
	float noise();
private:
	const int OCTAVES = 5;
};


#endif // !NOISE_GENERATOR_H



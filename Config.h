#pragma once
#ifndef CONFIG_H
#define CONFIG_H

struct Config
{
	static constexpr int MAX_LIGHTS = 4;
	static constexpr float MAX_PIXEL_COLOUR = 4294967296.0f;
	
	static constexpr float ASPECT_RATIO = 2.0f;
	static constexpr float NEAR = 0.1f;
	static constexpr float FAR = 1000.0f;
};

#endif // !CONFIG_H

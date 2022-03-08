#pragma once
#ifndef CONFIG_H
#define CONFIG_H

struct Config
{
	// Lighting values
	static constexpr int MAX_LIGHTS = 4;
	static constexpr float MAX_PIXEL_COLOUR = 4294967296.0f;
	
	// Matrix arguments
	static constexpr float ASPECT_RATIO = 2.0f;
	static constexpr float NEAR = 0.1f;
	static constexpr float FAR = 1000.0f;

	// Player physics
	static constexpr float GRAVITY = -0.5f;
	static constexpr float JUMP_STRENGTH = 18.0f;

	// Mouse values
	static constexpr float MAX_PITCH_ANGLE = 80.0f;
	static constexpr float MOUSE_SENSITIVITY = 0.05f;

	// World Generation
	static constexpr float VIEW_DISTANCE = 150.0f;
	static constexpr float CHUNK_SIZE = 100.0f;
	static constexpr int VERTEX_COUNT = 200;
	static constexpr float MAX_HEIGHT = 20.0f;

};

#endif // !CONFIG_H

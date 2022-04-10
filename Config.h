#pragma once
#ifndef CONFIG_H
#define CONFIG_H

struct Config
{
	// Lighting values
	inline static const int MAX_LIGHTS = 4;
	inline static const float MAX_PIXEL_COLOUR = 4294967296.0f;
	
	// Sky colour
	// purple 0.6, 0.1, 1.0
	inline static float RED = 0.6f;
	inline static float GREEN = 0.1f;
	inline static float BLUE = 1.0f;

	// TODO: Uniform variable fog settings
	inline static float FOG_DENSITY = 0.015f;
	inline static float FOG_GRADIENT = 2.0f;

	// Matrix arguments
	inline static const float ASPECT_RATIO = 2.0f;
	inline static const float NEAR = 0.1f;
	inline static const float FAR = 1000.0f;
	inline static const float FOV = 45.0f;

	// Player physics
	inline static const float GRAVITY = -0.5f;
	inline static const float JUMP_STRENGTH = 18.0f;

	// Mouse values
	inline static const float MAX_PITCH_ANGLE = 80.0f;
	inline static const float MOUSE_SENSITIVITY = 0.05f;

	// Chunk Generation
	inline static int RENDER_DISTANCE = 1;
	inline static const float CHUNK_SIZE = 100.0f;
	inline static const int VERTEX_COUNT = 42;
	inline static float MAX_HEIGHT = 30.0f;

	// Height generation
	inline static int SEED = -1;
	inline static float SCALE = 30.0f;
	inline static float PERSISTANCE = 0.6f;
	inline static float LACUNARITY = 2.2f;
	inline static int OCTAVES = 4;

};

#endif // !CONFIG_H

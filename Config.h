#pragma once
#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
	// Lighting values
	const int MAX_LIGHTS = 4;
	const float MAX_PIXEL_COLOUR = 4294967296.0f;
	
	// Sky colour
	// purple 0.6, 0.1, 1.0
	const float RED = 0.6f;
	const float GREEN = 0.1f;
	const float BLUE = 1.0f;

	// TODO: Uniform variable fog settings
	const float FOG_DENSITY = 0.0f;
	const float FOG_GRADIENT = 0.0f;

	// Matrix arguments
	const float ASPECT_RATIO = 2.0f;
	const float NEAR = 0.1f;
	const float FAR = 1000.0f;
	const float FOV = 45.0f;

	// Player physics
	const float GRAVITY = -0.5f;
	const float JUMP_STRENGTH = 18.0f;

	// Mouse values
	const float MAX_PITCH_ANGLE = 80.0f;
	const float MOUSE_SENSITIVITY = 0.05f;

	// Chunk Generation
	const int RENDER_DISTANCE = 1;
	const float CHUNK_SIZE = 100.0f;
	const int VERTEX_COUNT = 39;
	const float MAX_HEIGHT = 30.0f;

	// Height generation
	const float SCALE = 50.0f;
	const float PERSISTANCE = 0.6f;
	const float LACUNARITY = 2.2f;
	const int OCTAVES = 4;

};

#endif // !CONFIG_H

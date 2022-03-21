#pragma once
#ifndef SKYBOX_RENDERER_H
#define SKYBOX_RENDERER_H

#include "../TexturedModel.h"
#include "../Entities/Camera.h"
#include "../Util/ResourceManager.h"
#include "../Maths/Matrix.h"

class SkyboxRenderer
{
public:
	SkyboxRenderer();

	void render(const Camera& camera);

private:
	TexturedModel cubeModel;
};

#endif // !SKYBOX_RENDERER_H




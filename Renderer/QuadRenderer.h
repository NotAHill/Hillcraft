#pragma once
#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "../Model.h"
#include "../Maths/glm.h"
#include "../BasicShader.h"

#include <vector>

class Camera;

class QuadRenderer
{
public:
	QuadRenderer();
	void add(const Vector3& position);
	void render(const Camera& camera);

private:
	std::vector<Vector3> quads;
	Model quadModel;
	
	BasicShader shader;
	//int locationProjectionView;
	//int locationModel;
};


#endif // !QUADRENDERER_H


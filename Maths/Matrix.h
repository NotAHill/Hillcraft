#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera;
class Entity;

#include "../Entities/Camera.h"
#include "../Entities/Entity.h"

#include "../Config.h"

inline glm::mat4 makeModelMatrix(const Entity& entity)
{
	glm::mat4 matrix(entity.scale);

	matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, entity.position);

	return matrix;
}

inline glm::mat4 makeViewMatrix(const Camera& camera)
{
	glm::mat4 matrix(1.0f);

	matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -camera.position);

	return matrix;
}

inline glm::mat4 makeProjectionMatrix(float fov)
{
	return glm::perspective(glm::radians(fov), Config::ASPECT_RATIO, Config::NEAR, Config::FAR);
}

inline float barycentricInterpolation(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

/* Function to linearly interpolate between a0 and a1
 * Weight w should be in the range [0.0, 1.0]
 */
namespace
{
    float interpolate(float a0, float a1, float w) {
        /* // You may want clamping by inserting:
         * if (0.0 > w) return a0;
         * if (1.0 < w) return a1;
         */
        return (a1 - a0) * w + a0;
        /* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
         * return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
         *
         * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
         * return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
         */
    }

    /* Create pseudorandom direction vector
     */
    glm::vec2 randomGradient(int ix, int iy) {
        // No precomputed gradients mean this works for any number of grid coordinates
        const unsigned w = 8 * sizeof(unsigned);
        const unsigned s = w / 2; // rotation width
        unsigned a = ix, b = iy;
        a *= 3284157443; b ^= a << s | a >> w - s;
        b *= 1911520717; a ^= b << s | b >> w - s;
        a *= 2048419325;
        float random = fmodf((float)rand(), 2 * 3.141592f);//a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
        glm::vec2 v;
        v.x = cos(random); v.y = sin(random);
        return v;
    }

    // Computes the dot product of the distance and gradient vectors.
    float dotGridGradient(int ix, int iy, float x, float y) {
        // Get gradient from integer coordinates
        glm::vec2 gradient = randomGradient(ix, iy);

        // Compute the distance vector
        float dx = x - (float)ix;
        float dy = y - (float)iy;

        // Compute the dot-product
        return (dx * gradient.x + dy * gradient.y);
    }
}

// Compute Perlin noise at coordinates x, y
inline float perlin(float x, float y) {
    // Determine grid cell coordinates
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return value;
}

#endif // !MATRIX_H


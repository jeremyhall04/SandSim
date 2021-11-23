#ifndef PARTICLE_COLOR_H
#define PARTICLE_COLOR_H

#include <glm/glm.hpp>

struct color_t
{
	float r, g, b, a;
};



class colorSet
{
public:
	static void bg(color_t& c) { c.r = 0.3f; c.g = 0.5f; c.b = 0.8f; c.a = 1.0f; };
	static void black(color_t& c) { c.r = 1.0f; c.g = 1.0f; c.b = 1.0f; c.a = 1.0f; };
	static void grey(color_t& c) { c.r = 0.5f; c.g = 0.5f; c.b = 0.5f; c.a = 1.0f; };
	static void blue(color_t& c) { c.r = 0.0f; c.g = 0.0f; c.b = 1.0f; c.a = 1.0f; };
	static void yellow(color_t& c) { c.r = 0.8f; c.g = 0.8f; c.b = 0.0f; c.a = 1.0f; };
};

#endif // !PARTICLE_COLOR_H

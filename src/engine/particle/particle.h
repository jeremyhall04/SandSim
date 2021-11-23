#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include "particleColors.h"

struct VertexData
{
	float x, y, r, g, b;
};

enum class p_type
{
	empty,
	stone,
	sand,
	water,
};

struct Particle
{
	// id & lifetime
	p_type type = p_type::empty;
	glm::vec2 velocity;	// 8 bytes
	color_t color;	// 16 bytes
	bool updated = false;	// 2 byte
}; // 26 bytes

inline void setColor(Particle* p)
{
	switch (p->type)
	{
	case p_type::empty:
		colorSet::bg(p->color);
		break;
	case p_type::stone:
		colorSet::grey(p->color);
		break;
	case p_type::sand:
		colorSet::yellow(p->color);
		break;
	case p_type::water:
		colorSet::blue(p->color);
		break;
	}
}

#endif // !PARTICLE_H

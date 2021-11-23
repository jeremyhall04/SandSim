#include "physics.h"

void apply_gravity(Particle* p, float deltaTime)
{
	p->velocity.y += f_gravity * deltaTime;
	if (glm::abs(p->velocity.y) >= glm::abs(f_falling_max_vel))
		p->velocity.y = f_falling_max_vel;
	
	// start reducing x velocity 
	if (p->velocity.x > 0)
	{
		p->velocity.x -= glm::abs(f_falling_max_vel * glm::cos(p->velocity.y));
		if (p->velocity.x > 0)
			p->velocity.x = 0;
	}
	if (p->velocity.x < 0)
	{
		p->velocity.x += glm::abs(f_falling_max_vel * glm::cos(p->velocity.y));
		if (p->velocity.x > 0)
			p->velocity.x = 0;
	}
}

void apply_liquid_spread(Particle* p, float friction, int direction, float deltaTime)
{
	switch (p->type)
	{
	case p_type::water:
		p->velocity.x += direction * (f_water_spread_vel - f_water_spread_vel * f_water_friction)* deltaTime;
		if (glm::abs(p->velocity.x) > f_water_max_vel)
			p->velocity.x = f_water_max_vel * p->velocity.x / glm::abs(p->velocity.x);
		break;
	}
}

void apply_liquid_spread(Particle* pLiquid, Particle* pOther, int direction, float deltaTime)
{
	float friction = 0;
	switch (pOther->type)
	{
	case p_type::water:
		friction = f_water_friction;
		break;
	case p_type::stone:
		friction = f_stone_friction;
		break;
	case p_type::sand:
		friction = f_sand_friction;
		break;
	}
	apply_liquid_spread(pLiquid, friction, direction, deltaTime);
}

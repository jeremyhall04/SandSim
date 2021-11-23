#ifndef PHYSICS_H
#define PHYSICS_H

#include "../glHeader.h"
#include "../particle/particle.h"
const float f_gravity = -10.0f;
const float f_falling_max_vel = -3.0f;

const float f_water_spread_vel = 4.0f;
const float f_water_max_vel = 4.0f;
const float f_water_friction = 0.01f;

const float f_sand_friction = 0.05f;
const float f_stone_friction = 0.05f;

void apply_gravity(Particle* p, float deltaTime);
void apply_liquid_spread(Particle* p, float friction, int direction, float deltaTime);
void apply_liquid_spread(Particle* pLiquid, Particle* pOther, int direction, float deltaTime);


#endif // !PHYSICS_H

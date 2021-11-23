#ifndef PARTICLE_HANDLER_H
#define PARTICLE_HANDLER_H

#include "particle.h"
#include "../consts.h"
#include <vector>

static float particleSize = 2.0f;
const int gridWidth = (int)(SCR_WIDTH / particleSize);
const int gridHeight = (int)(SCR_HEIGHT / particleSize);
const int nMaxParticles = gridWidth * gridHeight;
const int vertex_size = 5 * sizeof(float);
const int buffer_size = vertex_size * gridWidth * gridHeight;

bool is_inbounds(int x, int y);
int to_index(int x, int y);
void get_p_between(const glm::vec2& start, const glm::vec2& end, std::vector<glm::vec2>& positions);

class ParticleHandler 
{
private:
	Particle* p;
	std::vector<glm::vec2> p_to_render;
	int activeParticles;
	float deltaTime;

public:
	ParticleHandler();
	
	void update(float deltaTime);
	Particle* get_p(int x, int y);
	Particle* get_p(const glm::vec2& pos);
	void initParticle(int xPos, int yPos, p_type type);
	void removeParticle(int xPos, int yPos);
	void clearRendereQueue();
	int getActiveParticles() { return activeParticles; };
	std::vector<glm::vec2> getRenderQueue() { return p_to_render; };
private:
	void update_stone(int x, int y);
	void update_sand(int x, int y);
	void update_sand_noPhysics(int x, int y);
	void update_water(int x, int y);
	void update_water_noPhysics(int x, int y);
	void move_particle(Particle* curr, Particle* next, glm::vec2 nextPos);
	void switch_particles(Particle* a, const glm::vec2& aPos, Particle* b, const glm::vec2& bPos);
	glm::vec2 calculate_next_position(Particle* p, float x_curr, float y_curr);
};

#endif // !PARTICLE_HANDLER_H

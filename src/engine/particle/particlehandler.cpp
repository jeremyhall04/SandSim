#include "particlehandler.h"
#include "../physics/physics.h"

ParticleHandler::ParticleHandler()
{
	p = new Particle[nMaxParticles];
	activeParticles = 0;
	deltaTime = 0;
}

void ParticleHandler::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	for (int y = gridHeight - 1; y > 0; y--)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			p_type type = get_p(x, y)->type;
			switch (type)
			{
			case p_type::stone:
				update_stone(x, y);
				break;
			case p_type::sand:
				update_sand(x, y);
				break;
			case p_type::water:
				update_water(x, y);
				break;
			}
		}
	}
}

Particle* ParticleHandler::get_p(int x, int y)
{
	return &p[to_index(x, y)];
}

Particle* ParticleHandler::get_p(const glm::vec2& pos)
{
	return get_p(pos.x, pos.y);
}

void ParticleHandler::initParticle(int xPos, int yPos, p_type type)
{
	Particle* p = get_p(xPos, yPos);
	if (p->type == p_type::empty)
	{
		p->type = type;
		setColor(p);
		p_to_render.push_back(glm::vec2(xPos, yPos));
		activeParticles++;
	}
}

void ParticleHandler::removeParticle(int xPos, int yPos)
{
	Particle* p = get_p(xPos, yPos);
	if (p->type != p_type::empty)
	{
		p->type = p_type::empty;
		p->velocity = glm::vec2(0);
		activeParticles - 1 >= 0 ? activeParticles-- : 0;
	}
}

void ParticleHandler::clearRendereQueue()
{
	p_to_render.clear();
}

void ParticleHandler::update_stone(int x, int y)
{
	p_to_render.push_back(glm::vec2(x, y));
}

void ParticleHandler::update_sand(int x0, int y0)
{
	glm::vec2 currPos = glm::vec2(x0, y0);
	glm::vec2 nextPos = currPos;
	Particle* curr = get_p(currPos);
	Particle* next = curr;
	if (curr->updated)
	{
		curr->updated = false;
		return;
	}

	Particle* down = get_p(x0, y0 - 1);
	if (down->type == p_type::empty)
	{
		apply_gravity(curr, deltaTime);
		int xDesired = x0 + curr->velocity.x;
		int yDesired = y0 + curr->velocity.y;
		std::vector<glm::vec2> positions_to_check;
		get_p_between(glm::vec2(x0, y0), glm::vec2(xDesired, yDesired), positions_to_check);
		for (glm::vec2 pos : positions_to_check)
		{
			Particle* p = get_p(pos.x, pos.y);
			if (p->type == p_type::empty)
			{
				next = p;
				nextPos = pos;
			}
		}
		move_particle(curr, next, nextPos);
	}
	else
	{
		curr->velocity = glm::vec2(0.0f);
		Particle* downL = get_p(x0 - 1, y0 - 1);
		Particle* downR = get_p(x0 + 1, y0 - 1);
		Particle* left = get_p(x0 - 1, y0);
		Particle* right = get_p(x0 + 1, y0);
		bool mleft, mright, rand;


		if (down->type == p_type::empty)
			move_particle(curr, down, glm::vec2(x0, y0 - 1));
		else if (down->type == p_type::water)
			switch_particles(curr, glm::vec2(x0, y0), down, glm::vec2(x0, y0 - 1));
		else if (downL->type == p_type::empty && downR->type == p_type::empty)
		{
			rand = std::rand() % 2;
			mleft = rand ? true : false;
			mright = rand ? false : true;
			if (mleft)
				move_particle(curr, downL, glm::vec2(x0 - 1, y0 - 1));
			else if (mright)
				move_particle(curr, downR, glm::vec2(x0 + 1, y0 - 1));
		}
		else if (downL->type == p_type::water && downR->type == p_type::water)
		{
			rand = std::rand() % 2;
			mleft = rand ? true : false;
			mright = rand ? false : true;
			if (mleft)
				switch_particles(curr, glm::vec2(x0, y0), downL, glm::vec2(x0 - 1, y0 - 1));
			else if (mright)
				switch_particles(curr, glm::vec2(x0, y0), downR, glm::vec2(x0 + 1, y0 - 1));
		}
		else if (downL->type == p_type::empty)
			move_particle(curr, downL, glm::vec2(x0 - 1, y0 - 1));
		else if (downL->type == p_type::water)
			switch_particles(curr, glm::vec2(x0, y0), downL, glm::vec2(x0 - 1, y0 - 1));
		else if (downR->type == p_type::empty)
			move_particle(curr, downR, glm::vec2(x0 + 1, y0 - 1));
		else if (downR->type == p_type::water)
			switch_particles(curr, glm::vec2(x0, y0), downR, glm::vec2(x0 + 1, y0 - 1));
		else
			move_particle(curr, curr, glm::vec2(x0, y0));
	}

	//Particle* downL = get_p(x0 - 1, y0 - 1);
	//Particle* downR = get_p(x0 + 1, y0 - 1);
	//Particle* left = get_p(x0 - 1, y0);
	//Particle* right = get_p(x0 + 1, y0);
	//if (down->type == p_type::empty)
	//	move_particle(curr, down, glm::vec2(x0, y0 - 1));
	//else if (down->type == p_type::water)
	//	switch_particles(curr, glm::vec2(x0, y0), down, glm::vec2(x0, y0 - 1));
	//else if (downL->type == p_type::empty)
	//	move_particle(curr, downL, glm::vec2(x0 - 1, y0 - 1));
	//else if (downL->type == p_type::water)
	//	switch_particles(curr, glm::vec2(x0, y0), downL, glm::vec2(x0 - 1, y0 - 1));
	//else if (downR->type == p_type::empty)
	//	move_particle(curr, downR, glm::vec2(x0 + 1, y0 - 1));
	//else if (downR->type == p_type::water)
	//	switch_particles(curr, glm::vec2(x0, y0), downR, glm::vec2(x0 + 1, y0 - 1));
	//else
	//	move_particle(curr, curr, glm::vec2(x0, y0));
}

// No physics
void ParticleHandler::update_sand_noPhysics(int x0, int y0)
{
	glm::vec2 currPos = glm::vec2(x0, y0);
	glm::vec2 nextPos = currPos;
	Particle* curr = get_p(currPos);
	Particle* next = curr;
	if (curr->updated)
	{
		curr->updated = false;
		return;
	}

	Particle* down = get_p(x0, y0 - 1);
	Particle* downL = get_p(x0 - 1, y0 - 1);
	Particle* downR = get_p(x0 + 1, y0 - 1);
	Particle* left = get_p(x0 - 1, y0);
	Particle* right = get_p(x0 + 1, y0);
	if (down->type == p_type::empty)
		move_particle(curr, down, glm::vec2(x0, y0 - 1));
	else if (down->type == p_type::water)
		switch_particles(curr, glm::vec2(x0, y0), down, glm::vec2(x0, y0 - 1));
	else if (downL->type == p_type::empty)
		move_particle(curr, downL, glm::vec2(x0 - 1, y0 - 1));
	else if (downL->type == p_type::water)
		switch_particles(curr, glm::vec2(x0, y0), downL, glm::vec2(x0 - 1, y0 - 1));
	else if (downR->type == p_type::empty)
		move_particle(curr, downR, glm::vec2(x0 + 1, y0 - 1));
	else if(downR->type == p_type::water)
		switch_particles(curr, glm::vec2(x0, y0), downR, glm::vec2(x0 + 1, y0 - 1));
	else
		move_particle(curr, curr, glm::vec2(x0, y0));
}

// Physics
void ParticleHandler::update_water(int x0, int y0)
{
	//deltaTime = 0.5f;
	Particle* curr = get_p(x0, y0);
	Particle* next = curr;
	glm::vec2 currPos(x0, y0);
	glm::vec2 nextPos = currPos;
	if (curr->updated)
	{
		curr->updated = false;
		return;
	}

	std::vector<glm::vec2> positions_to_check;
	Particle* down = get_p(x0, y0 - 1);
	if (down->type == p_type::empty)
	{
		apply_gravity(curr, deltaTime);
		int xDesired = x0 + curr->velocity.x;
		int yDesired = y0 + curr->velocity.y;
		get_p_between(glm::vec2(x0, y0), glm::vec2(xDesired, yDesired), positions_to_check);
		for (glm::vec2 pos : positions_to_check)
		{
			Particle* p = get_p(pos.x, pos.y);
			if (p->type == p_type::empty)
			{
				next = p;
				nextPos = pos;
			}
		}
		move_particle(curr, next, nextPos);
	}
	else
	{
		curr->velocity.y = 0;	// stop velocity downward
		Particle* downL = get_p(x0 - 1, y0 - 1);
		Particle* downR = get_p(x0 + 1, y0 - 1);
		Particle* left = get_p(x0 - 1, y0);
		Particle* right = get_p(x0 + 1, y0);
		bool needToUpdate = false;
		bool mleft = true, mright = true, rand;
		//if (curr->velocity.x == 0 && left->type == p_type::empty && right->type == p_type::empty)
		///*if (left->type == p_type::empty && right->type == p_type::empty)*/
		//{
		//	rand = std::rand() % 2;
		//	mleft = rand ? true : false;
		//	mright = rand ? false : true;
		//}

		//if (mleft && left->type == p_type::empty)
		//	apply_liquid_spread(curr, -1, deltaTime);
		//else if (mright && right->type == p_type::empty)
		//{
		//	apply_liquid_spread(curr, 1, deltaTime);
		//	needToUpdate = true;
		//}
		if (mright && right->type == p_type::empty)
		{
			if (curr->velocity.x == 0)
				apply_liquid_spread(curr, 0.0f, 1, deltaTime);
			else
				apply_liquid_spread(curr, down, 1, deltaTime);
			needToUpdate = true;
		}
		else if (mleft && left->type == p_type::empty)
			apply_liquid_spread(curr, down, -1, deltaTime);
		else
			curr->velocity.x = 0;
		
		int xDesired = x0 + curr->velocity.x;
		int yDesired = y0 + curr->velocity.y;
		get_p_between(glm::vec2(x0, y0), glm::vec2(xDesired, yDesired), positions_to_check);
		for (glm::vec2 pos : positions_to_check)
		{
			Particle* p = get_p(pos.x, pos.y);
			if (p->type == p_type::empty || p == curr)
			{
				next = p;
				nextPos = pos;
			}
		}
		move_particle(curr, next, nextPos);
		next->updated = needToUpdate;
	}
}

// OLD (No physics)
void ParticleHandler::update_water_noPhysics(int x0, int y0)
{
	Particle* curr = get_p(x0, y0);
	Particle* next = curr;
	glm::vec2 currPos(x0, y0);
	glm::vec2 nextPos = currPos;
	if (curr->updated)
	{
		curr->updated = false;
		return;
	}

	Particle* down = get_p(x0, y0 - 1);
	Particle* downL = get_p(x0 - 1, y0 - 1);
	Particle* downR = get_p(x0 + 1, y0 - 1);
	Particle* left = get_p(x0 - 1, y0);
	Particle* right = get_p(x0 + 1, y0);
	int xNext = x0, yNext = y0;
	if (down->type == p_type::empty)
		move_particle(curr, down, glm::vec2(x0, y0 - 1));
	else if (left->type == p_type::empty && curr->velocity.x <= 0)
	{
		//xNext = x0 - 1;
		for (int i = 1; i <= (int)f_water_spread_vel; i++)
		{
			xNext = x0 - i;
			Particle* p = get_p(xNext, yNext);
			if (p->type == p_type::empty)
			{
				curr->velocity.x = -1;
				left = p;
			}
		}
		move_particle(curr, left, glm::vec2(xNext, yNext));
	}
	else if (right->type == p_type::empty && curr->velocity.x >= 0)
	{
		//xNext = x0 + 1;
		for (int i = 1; i <= (int)f_water_spread_vel; i++)
		{
			xNext = x0 + i;
			Particle* p = get_p(xNext, yNext);
			if (p->type == p_type::empty)
			{
				curr->velocity.x = 1;
				left = p;
			}
		}
		move_particle(curr, right, glm::vec2(xNext, yNext));
	}
	else
	{
		curr->velocity.x = 0;
		move_particle(curr, curr, glm::vec2(x0, y0));
	}

	//if (down->type == p_type::empty)
	//	move_particle(curr, down, glm::vec2(x0, y0 - 1));
	//else if (downL->type == p_type::empty && left->type == p_type::empty)
	//	move_particle(curr, downL, glm::vec2(x0 - 1, y0 - 1));
	//else if (downR->type == p_type::empty && right->type == p_type::empty)
	//	move_particle(curr, downR, glm::vec2(x0 + 1, y0 - 1));
	//else if (left->type == p_type::empty)
	//	move_particle(curr, left, glm::vec2(x0 - 1, y0));
	//else if (right->type == p_type::empty)
	//	move_particle(curr, right, glm::vec2(x0 + 1, y0));
	//else
	//	move_particle(curr, curr, glm::vec2(x0, y0));
}

void ParticleHandler::move_particle(Particle* curr, Particle* next, glm::vec2 nextPos)
{
	if (nextPos.x < 0)
		nextPos.x = 0;
	if (nextPos.x > gridWidth)
		nextPos.x = gridWidth - 1;
	if (nextPos.y < 0)
		nextPos.y = 0;
	if (nextPos.y > gridHeight)
		nextPos.y = gridHeight - 1;
	if (curr != next)
	{
		next->type = curr->type;
		next->velocity = curr->velocity;
		setColor(next);
		next->updated = true;
		curr->type = p_type::empty;
		curr->velocity = glm::vec2(0);
	}
	p_to_render.push_back(glm::vec2(nextPos.x, nextPos.y));
}

void ParticleHandler::switch_particles(Particle* a, const glm::vec2& aPos, Particle* b, const glm::vec2& bPos)
{
	Particle temp = *b;
	move_particle(a, b, bPos);	// a moved to b
	move_particle(&temp, a, aPos);// b moved to a
}

glm::vec2 ParticleHandler::calculate_next_position(Particle* p, float x_curr, float y_curr)
{
	glm::vec2 curr_vel = p->velocity;
	glm::vec2 curr_pos(x_curr, y_curr), next_pos;

	// calculate next position
	next_pos.x = curr_pos.x + curr_vel.x;
	next_pos.y = curr_pos.y + curr_vel.y;

	// cast ray to next position & stop if hit another particle

	// return the calculated position
	return next_pos;
}

bool is_inbounds(int x, int y)
{
	return x > 0 && x < gridWidth && y > 0 && y < gridHeight;
}

int to_index(int x, int y)
{
	if (x <= 0)
		x = 0;
	if (x >= gridWidth)
		x = gridWidth - 1;
	if (y >= gridHeight)
		y = gridHeight - 1;
	if (y <= 0)
		y = 0;
	return y * gridHeight + x;
}

void get_p_between(const glm::vec2& start, const glm::vec2& end, std::vector<glm::vec2>& positions)
{
	if (start == end)
		return;

	int xDiff = start.x - end.x, yDiff = start.y - end.y;
	bool xDiffIsLarger = glm::abs(xDiff) > glm::abs(yDiff);

	int xModifier = xDiff < 0 ? 1 : -1;
	int yModifier = yDiff < 0 ? 1 : -1;

	int longerLength = glm::max(glm::abs(xDiff), glm::abs(yDiff));
	int shorterLength = glm::min(glm::abs(xDiff), glm::abs(yDiff));

	float slope = (shorterLength == 0 || longerLength == 0) ? 0 : ((float)(shorterLength) / (longerLength));
	int shortSideIncrease;

	for (int i = 1; i <= longerLength; i++)
	{
		shortSideIncrease = glm::round(i * slope);
		int xIncrease, yIncrease;
		if (xDiffIsLarger)
		{
			xIncrease = i;
			yIncrease = shortSideIncrease;
		}
		else
		{
			xIncrease = shortSideIncrease;
			yIncrease = i;
		}
		int currentX = start.x + (xIncrease * xModifier);
		int currentY = start.y + (yIncrease * yModifier);
		positions.push_back(glm::vec2(currentX, currentY));
	}

	//	glm::vec2 check = start;
	//if (delX > 0)		// MOVING RIGHT (positive slope)
	//{
	//	if (delY < 0)	// MOVING DOWN
	//	{
	//		slope = delY / delX;
	//		int x = start.x + 1, y = start.y - 1;
	//		int step = slope / glm::abs(slope);
	//		check = glm::vec2(x, y);
	//		float yp;
	//		while (glm::abs(check.x - end.x) > 0 || glm::abs(check.y - end.y) > 0)
	//		{
	//			yp = -slope * (float)x;
	//			y = std::round(yp);
	//			check = glm::vec2(x, y);
	//			positions.push_back(check);
	//			//printf("\n%d, %d", x, y);
	//			x += step;
	//		}
	//	}
	//	else if (delY > 0)	// MOVING UP
	//	{
	//		slope = delY / delX;
	//		int x = start.x + 1, y = start.y + 1;
	//		int step = slope / glm::abs(slope);
	//		check = glm::vec2(x, y);
	//		float yp;
	//		while (glm::abs(check.x - end.x) > 0 || glm::abs(check.y - end.y) > 0)
	//		{
	//			yp = slope * (float)x;
	//			y = std::round(yp);
	//			check = glm::vec2(x, y);
	//			positions.push_back(check);
	//			//printf("\n%d, %d", x, y);
	//			x += step;
	//		}
	//	}
	//	else
	//	{
	//		int x = start.x + 1, y = start.y;
	//		check = glm::vec2(x, y);
	//		float yp;
	//		while (check.x != end.x)
	//		{
	//			check = glm::vec2(x, y);
	//			positions.push_back(check);
	//			//printf("\n%d, %d", x, y);
	//			x += 1;
	//		}
	//	}
	//}
	//else if (delX < 0)	// MOVING LEFT
	//{
	//	if (delY < 0)	// MOVING DOWN
	//	{
	//		slope = delY / delX;
	//		slope = 1 / slope;
	//		int x = start.x - 1, y = start.y - 1;
	//		float yp;
	//		int step = -1;
	//		check = glm::vec2(x, y);
	//		while (glm::abs(check.x - end.x) > 0 || glm::abs(check.y - end.y) > 0)
	//		{
	//			yp = -slope * (float)x;
	//			y = std::round(yp);
	//			check = glm::vec2(x, y);
	//			positions.push_back(check);
	//			//printf("\n%d, %d", x, y);
	//			x += step;
	//		}
	//	}
	//	else if (delY > 0)	// MOVING UP
	//	{
	//		slope = delY / delX;
	//		int x = start.x - 1, y = start.y + 1;
	//		float yp;
	//		int step = slope / glm::abs(slope);
	//		check = glm::vec2(x, y);
	//		while (glm::abs(check.x - end.x) > 0 || glm::abs(check.y - end.y) > 0)
	//		{
	//			yp = slope * (float)x;
	//			y = std::round(yp);
	//			check = glm::vec2(x, y);
	//			positions.push_back(check);
	//			//printf("\n%d, %d", x, y);
	//			x += step;
	//		}
	//	}
	//	else
	//	{
	//		int x = start.x - 1, y = start.y;
	//		float yp;
	//		check = glm::vec2(x, y);
	//		while (check.x != end.x)
	//		{
	//			check = glm::vec2(x, y);
	//			positions.push_back(check);
	//			//printf("\n%d, %d", x, y);
	//			x -= 1;
	//		}
	//	}
	//}
	//else
	//{								// MOVING VERTICAL (inf. slope)
	//	slope = (end.y - start.y);
	//	int step = slope / glm::abs(slope);
	//	int x = start.x, y = start.y + step;
	//	check = glm::vec2(x, y);
	//	while (check.y != end.y)
	//	{
	//		check = glm::vec2(x, y);
	//		positions.push_back(check);
	//		//printf("\n%d, %d", x, y);
	//		y += step;
	//	}
	//}
}
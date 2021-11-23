#ifndef PENCIL_H
#define PENCIL_H

#include "particlehandler.h"
#include "../glHeader.h"

class Pencil
{
	ParticleHandler* pHandler;
	p_type p_Type;
	int pencilRad;
	int eraserRad;

public:
	Pencil();
	Pencil(int pencilRadius, int eraserRadius, p_type type);
	~Pencil();

private:
	void init();
	void process_input(GLFWwindow* context);
	void clear_active_particles();
public:
	void update(GLFWwindow* context, float deltaTime);
	ParticleHandler* getHandler() { return pHandler; };
	void draw(int xPos, int yPos);
	void erase(int xPos, int yPos);
	void setPencilType(p_type type) { p_Type = type; };
	void setPencilSize(int size) { pencilRad = size; };
	void setEraserSize(int size) { eraserRad = size; };
};

#endif // !PENCIL_H

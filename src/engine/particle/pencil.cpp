#include "pencil.h"
#include "../window/input.h"

Pencil::Pencil()
{
	pencilRad = 3;
	eraserRad = 5;
	p_Type = p_type::stone;
	init();
}

Pencil::Pencil(int pencilRadius, int eraserRadius, p_type type)
	: pencilRad(pencilRadius), eraserRad(eraserRadius), p_Type(type)
{
	init();
}

Pencil::~Pencil()
{
	if (pHandler != NULL)
		delete pHandler;
	pHandler = NULL;
}

void Pencil::init()
{
	pHandler = new ParticleHandler;
}

void Pencil::update(GLFWwindow* context, float deltaTime)
{
	if (Input::isKeyPressed(context, GLFW_KEY_C))
		clear_active_particles();
	pHandler->clearRendereQueue();
	process_input(context);
	pHandler->update(deltaTime);
}

static bool is_pressed_LeftBracket = false, is_pressed_RightBracket = false;
void Pencil::process_input(GLFWwindow* context)
{
	if (Input::isKeyPressed(context, GLFW_KEY_1))
		p_Type = p_type::stone;
	if (Input::isKeyPressed(context, GLFW_KEY_2))
		p_Type = p_type::sand;
	if (Input::isKeyPressed(context, GLFW_KEY_3))
		p_Type = p_type::water;

	if (!is_pressed_LeftBracket && Input::isKeyPressed(context, GLFW_KEY_LEFT_BRACKET))
	{
		is_pressed_LeftBracket = true;
		pencilRad = pencilRad - 1 >= 0 ? pencilRad - 1 : 0;
	}
	if (is_pressed_LeftBracket && Input::isKeyReleased(context, GLFW_KEY_LEFT_BRACKET))
		is_pressed_LeftBracket = false;

	if (!is_pressed_RightBracket && Input::isKeyPressed(context, GLFW_KEY_RIGHT_BRACKET))
	{
		is_pressed_RightBracket = true;
		pencilRad = pencilRad + 1 <= 10 ? pencilRad + 1 : 10;
	}
	if (is_pressed_RightBracket && Input::isKeyReleased(context, GLFW_KEY_RIGHT_BRACKET))
		is_pressed_RightBracket = false;

	glm::vec2 mPos = Input::getMousePos(context);
	mPos.x /= particleSize;
	mPos.y = (SCR_HEIGHT - mPos.y) / particleSize;
	if (Input::isMouseButtonPressed(context, GLFW_MOUSE_BUTTON_1))
		draw(mPos.x, mPos.y);
	if (Input::isMouseButtonPressed(context, GLFW_MOUSE_BUTTON_2))
		erase(mPos.x, mPos.y);
}

void Pencil::clear_active_particles()
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			pHandler->removeParticle(i, j);
		}
	}
	printf("\nScreen Cleared");
}

void Pencil::draw(int xPos, int yPos)
{
	int nParticles = 2 * pencilRad * (pencilRad + 1) + 1;
	int x, y;

	for (int i = -pencilRad; i <= pencilRad; i++)
	{
		for (int j = -pencilRad; j <= pencilRad; j++)
		{
			x = xPos - i;
			y = yPos - j;
			if (glm::abs(x - xPos) + glm::abs(y - yPos) <= pencilRad)
				pHandler->initParticle(x, y, p_Type);
			x = xPos + i;
			y = yPos + j;
			if (glm::abs(x - xPos) + glm::abs(y - yPos) <= pencilRad)
				pHandler->initParticle(x, y, p_Type);
		}
	}
}

void Pencil::erase(int xPos, int yPos)
{
	int nParticles = 2 * eraserRad * (eraserRad + 1) + 1;
	int x, y;

	for (int i = -eraserRad; i <= eraserRad; i++)
	{
		for (int j = -eraserRad; j <= eraserRad; j++)
		{
			x = xPos - i;
			y = yPos - j;
			if (glm::abs(x - xPos) + glm::abs(y - yPos) <= eraserRad)
				pHandler->removeParticle(x, y);
			x = xPos + i;
			y = yPos + j;
			if (glm::abs(x - xPos) + glm::abs(y - yPos) <= eraserRad)
				pHandler->removeParticle(x, y);
		}
	}
}

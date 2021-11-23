#include <iostream>
#include "engine/window/window.h"
#include "engine/window/input.h"
#include "engine/utils/camera.h"
#include "engine/graphics/renderer.h"
#include "engine/particle/pencil.h"

const float buffer_time = 0.01f;

int main()
{
	Window window("Sand Simulator", Version::_430);
	g_Camera2d = new OrthoCamera(glm::vec2(0, gridWidth), glm::vec2(0, gridHeight), -1.0f, 1.0f);
	Renderer renderer;
	Shader* shader = renderer.shader;
	Pencil pencil(1, 5, p_type::stone);

	std::vector<glm::vec2> pos;
	pencil.setPencilSize(1);
	get_p_between(glm::vec2(0,1), glm::vec2(gridWidth, 1), pos);
	for (glm::vec2 p : pos)
		pencil.draw(p.x, p.y);
	pos.clear();
	get_p_between(glm::vec2(0, 1), glm::vec2(0, 5), pos);
	for (glm::vec2 p : pos)
		pencil.draw(p.x, p.y);
	pos.clear();
	get_p_between(glm::vec2(gridWidth, 1), glm::vec2(gridWidth, 5), pos);
	for (glm::vec2 p : pos)
		pencil.draw(p.x, p.y);
	pos.clear();

	pencil.setPencilSize(0);
	pencil.setPencilType(p_type::water);
	pencil.draw(50, 80);

	Shader computeShader("res/shaders/test.comp", computeType);

	printf("\nRenderable Particles = %d", gridWidth * gridHeight);
	printf("\nParticle buffer size = %f mb", buffer_size / 1000000.0f);


	float startTime = (float)glfwGetTime();
	float currTime = startTime;
	float deltaTime = 0;
	bool keyPressed = false;
	while (window.isActive())
	{
		window.clear();
		window.processInput();

		currTime = (float)glfwGetTime();
		deltaTime = currTime - startTime;
		if (deltaTime >= buffer_time)
		{
			startTime = currTime;
			pencil.update(window.context, deltaTime);
		}

		renderer.addParticlesToRenderQueue(pencil.getHandler());

		shader->enable();
		shader->setUniformMat4("projectionMatrix", g_Camera2d->getProjectionMatrix());
		shader->setUniformMat4("viewMatrix", g_Camera2d->getViewMatrix());

		renderer.render(pencil.getHandler());

		window.update();
	}

	return 0;
}
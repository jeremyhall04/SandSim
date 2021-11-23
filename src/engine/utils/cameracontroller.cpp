#include "cameracontroller.h"
#include "camera.h"
#include "../window/input.h"

void OrthoCameraController::processInput(GLFWwindow* context, float deltaTime)
{
	glm::vec3 newPos = g_Camera2d->getPosition();
	float velocity = m_2DCameraSpeed * deltaTime;

	if (Input::isKeyPressed(context, GLFW_KEY_A))
		newPos.x -= velocity;
	if (Input::isKeyPressed(context, GLFW_KEY_D))
		newPos.x += velocity;
	if (Input::isKeyPressed(context, GLFW_KEY_W))
		newPos.y += velocity;
	if (Input::isKeyPressed(context, GLFW_KEY_S))
		newPos.y -= velocity;

	g_Camera2d->setPosition(newPos);
}

void PerspectiveCameraController::processInput(GLFWwindow* context, float deltaTime)
{
	glm::vec3 newPos = g_Camera3d->getPosition();
	float velocity = m_3DCameraSpeed * deltaTime;

	if (Input::isKeyPressed(context, GLFW_KEY_W))
		newPos -= glm::vec3(g_Camera3d->getDirection().x * velocity, 0.0f, g_Camera3d->getDirection().z * velocity);
	if (Input::isKeyPressed(context, GLFW_KEY_S))
		newPos += glm::vec3(g_Camera3d->getDirection().x * velocity, 0.0f, g_Camera3d->getDirection().z * velocity);
	if (Input::isKeyPressed(context, GLFW_KEY_A))
		newPos -= glm::vec3(g_Camera3d->getRight().x * velocity, 0.0f, g_Camera3d->getRight().z * velocity);
	if (Input::isKeyPressed(context, GLFW_KEY_D))
		newPos += glm::vec3(g_Camera3d->getRight().x * velocity, 0.0f, g_Camera3d->getRight().z * velocity);
	if (Input::isKeyPressed(context, GLFW_KEY_SPACE))
		newPos.y += velocity;
	if (Input::isKeyPressed(context, GLFW_KEY_LEFT_SHIFT))
		newPos.y -= velocity;

	g_Camera3d->setPosition(newPos);
}

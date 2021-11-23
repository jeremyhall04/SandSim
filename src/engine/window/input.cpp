#include "input.h"

GLFWwindow* Input::context = nullptr;
int Input::key_pressed_code = 0;
// returns TRUE if GLFW_PRESS or GLFW_REPEAT, and FALSE otherwise
bool Input::isKeyPressed(GLFWwindow* context, int keycode)
{
	int state = glfwGetKey(context, keycode);
	key_pressed_code = state == GLFW_PRESS || state == GLFW_REPEAT ? keycode : 0;
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isKeyReleased(GLFWwindow* context, int keycode)
{
	int state = glfwGetKey(context, keycode);
	key_pressed_code = state == GLFW_RELEASE ? 0 : keycode;
	return state == GLFW_RELEASE;
}

bool Input::check_is_pressed(int keycode)
{
	return key_pressed_code == keycode;
}

float Input::isMouseButtonPressed(GLFWwindow* context, int button)
{
	int state = glfwGetMouseButton(context, button);
	return state == GLFW_PRESS;
}

glm::vec2 Input::getMousePos(GLFWwindow* context)
{
	double x, y;
	glfwGetCursorPos(context, &x, &y);
	return glm::vec2(x, y);
}

float Input::getMouseX(GLFWwindow* context)
{
	glm::vec2 pos;
	pos = getMousePos(context);
	return pos.x;
}

float Input::getMouseY(GLFWwindow* context)
{
	glm::vec2 pos;
	pos = getMousePos(context);
	return pos.y;
}

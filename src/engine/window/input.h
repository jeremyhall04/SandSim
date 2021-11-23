#ifndef INPUT_H
#define INPUT_H

#include "../glHeader.h"

class Input
{
private:
	static GLFWwindow* context;
	static int key_pressed_code;
public:
	static bool isKeyPressed(GLFWwindow* context, int keycode);
	static bool isKeyReleased(GLFWwindow* context, int keycode);
	static bool check_is_pressed(int keycode);
	static float isMouseButtonPressed(GLFWwindow* context, int button);
	static glm::vec2 getMousePos(GLFWwindow* context);
	static float getMouseX(GLFWwindow* context);
	static float getMouseY(GLFWwindow* context);
};

//class Input
//{
//private:
//	static Input* s_Instance;
//public:
//	static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); };
//protected:
//	virtual bool isKeyPressedImpl(int keycode) = 0;
//};

#endif // !INPUT_H

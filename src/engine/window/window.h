#ifndef WINDOW_H
#define WINDOW_H

#include "../glHeader.h"
#include "../consts.h"

enum class Version
{
	_330,
	_430,
};

class Window
{
private:
	const char* Title;
	Version gl_context_v;
public:
	GLFWwindow* context;

public:
	// OpenGL context v3.30 if no version specified;
	Window();
	Window(const char* windowTitle);
	Window(const char* windowTitle, Version gl_context_v);
	~Window();

private:
	void init();
public:
	bool isActive();
	void update();
	void clear();
	void processInput();
	void getMousePos(double& x, double& y);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif


#include "window.h"
#include "input.h"
#include "../utils/camera.h"
#include "../utils/cameracontroller.h"
#include "../utils/timer.h"
#include <iostream>

bool isWireframe = false;
Timer time;
float timer = 0.0f;
UINT frames = 0;
float deltaTime = 0.0f, lastFrame = 0.0f;

Window::Window()
{
	Title = "OpenGL Application";
	gl_context_v = Version::_330;
	init();
}

Window::Window(const char* windowTitle)
{
	Title = windowTitle;
	gl_context_v = Version::_330;
	init();
}

Window::Window(const char* windowTitle, Version gl_context_v)
{
	Title = windowTitle;
	this->gl_context_v = gl_context_v;
	init();
}

Window::~Window()
{
}

bool Window::isActive()
{
	return !glfwWindowShouldClose(context);
}

void Window::init()
{
	glfwInit();

	switch (gl_context_v)
	{
	case Version::_330:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		printf("\n--- OpenGL Version %s ---\n", "3.30");
		break;
	case Version::_430:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		printf("\n--- OpenGL Version %s ---\n", "4.30");
		break;
	}
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	printf("\nGLFW version %s\n", glfwGetVersionString());

	context = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, Title, NULL, NULL);
	if (context == NULL)
	{
		std::cout << "ERROR::GLFW::WINDOW CREATION FAILED\n" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(context);
	glfwSetFramebufferSizeCallback(context, framebuffer_size_callback);
	//glfwSetCursorPosCallback(handle, mouse_callback);
	//glfwSetMouseButtonCallback(handle, mouse_button_callback);
	//glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(0); // 0 for uncapped fps

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::GLAD INITIALIZATION FAILED\n" << std::endl;
		exit(1);
	}
}

void Window::update()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "\nERROR::WINDOW::UPDATE::OpenGl error::" << error;

	g_Camera2d->update();

	if (isWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSwapBuffers(context);
	glfwPollEvents();

	frames++;
	if (time.elapsed() - timer > 1.0f)
	{
		timer += 1.0f;
		printf("\n%d fps", frames);
		frames = 0;
	}
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::processInput()
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
	if (Input::isKeyPressed(context, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(context, true);

	//OrthoCameraController::processInput(context, deltaTime);

	static bool wasPressed;
	if (Input::isKeyPressed(context, GLFW_KEY_O) && !wasPressed)
	{
		isWireframe = !isWireframe;
		wasPressed = true;
	}
	else if (!Input::isKeyPressed(context, GLFW_KEY_O))
		wasPressed = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
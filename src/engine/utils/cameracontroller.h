#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "../glHeader.h"

enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class OrthoCameraController
{
public:
	static void processInput(GLFWwindow* context, float deltaTime);
};

class PerspectiveCameraController
{
public:
	static void processInput(GLFWwindow* context, float deltaTime);
};

//class CameraController
//{
//private:
//	static CameraController* s_Instance;
//
//public:
//	static void processKeyboardInput(CameraMovement direction, float deltaTime) { s_Instance->processKeyboardInputImpl(direction, deltaTime); };
//	static void processMouseMovement(float xOffset, float yOffset) { s_Instance->processMouseMovementImpl(xOffset, yOffset); };
//
//protected:
//	virtual void processKeyboardInputImpl(CameraMovement direction, float deltaTime) = 0;
//	virtual void processMouseMovementImpl(float xOffset, float yOffset) = 0;
//};
//
//class OrthoCameraController : CameraController
//{
//protected:
//	void processKeyboardInputImpl(CameraMovement direction, float deltaTime) override;
//	void processMouseMovementImpl(float xOffset, float yOffset) override;
//};
//
//class PerspectiveCameraController : CameraController
//{
//protected:
//	void processKeyboardInputImpl(CameraMovement direction, float deltaTime) override;
//	void processMouseMovementImpl(float xOffset, float yOffset) override;
//};

#endif // !CAMERA_CONTROLLER_H

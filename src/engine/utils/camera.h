#ifndef CAMERA_H
#define CAMERA_H

#include "../glHeader.h"
#include "cameracontroller.h"

const float m_3DCameraSpeed = 8.0f;
const float m_2DCameraSpeed = 2.0f;
const float m_MouseSensitivity = 0.1f;
static bool m_FirstMouse = true;
static float m_MouseLastX, m_MouseLastY;

struct ViewProjectionMatrices {
	glm::mat4 view, perspective;
};

//-----------------------------------------------------------------------------------------------------
//------------------------------------------- Base Camera Class ---------------------------------------
//-----------------------------------------------------------------------------------------------------

class Camera
{
protected:
	ViewProjectionMatrices m_ViewProj;
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	const glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 direction);
	~Camera();

	glm::mat4 getViewMatrix() { return m_ViewProj.view; };
	glm::mat4 getProjectionMatrix() { return m_ViewProj.perspective; };
	const glm::vec3& getPosition() { return m_Position; };
	void setPosition(const glm::vec3& pos) { m_Position = pos; };
	const glm::vec3& getDirection() { return m_Direction; };
	void setDirection(const glm::vec3& dir) { m_Direction = dir; };
	const glm::vec3& getRight() { return m_Right; };
	const glm::vec3& getUp() { return m_Up; };
};








//-----------------------------------------------------------------------------------------------------
//------------------------------------------- Orthographic --------------------------------------------
//-----------------------------------------------------------------------------------------------------

class OrthoCamera : public Camera
{
private:
	glm::vec2 m_HorLimits, m_VertLimits;
	float zFar, zNear;
public:
	OrthoCamera();
	OrthoCamera(glm::vec2 h_limits, glm::vec2 v_limits);
	OrthoCamera(glm::vec2 h_limits, glm::vec2 v_limits, float zFar, float zNear);
	OrthoCamera(glm::vec3 position, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits);
	OrthoCamera(glm::vec3 position, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits, float zFar, float zNear);
	OrthoCamera(float xPos, float yPos, float zPos, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits);
	OrthoCamera(float xPos, float yPos, float zPos, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits, float zFar, float zNear);

	void init();
	void update();
};







//-----------------------------------------------------------------------------------------------------
//------------------------------------------- Perspective ---------------------------------------------
//-----------------------------------------------------------------------------------------------------

class PerspectiveCamera : public Camera
{
private:
	float m_FOV, m_Aspect, m_zNear, m_zFar;
	float m_Pitch, m_Yaw;
public:
	PerspectiveCamera();
	PerspectiveCamera(glm::vec3 position, glm::vec3 direction, float fov);
	PerspectiveCamera(float xPos, float yPos, float zPos, glm::vec3 direction, float fov);

	void update();
	void processKeyboardInput(CameraMovement direction, float deltaTime);
	void processMouseMovement(float xOffset, float yOffset);
	const glm::vec4& getPerspectiveParams() const { return glm::vec4(m_FOV, m_Aspect, m_zNear, m_zFar); };
	void updateAspect(float aspect) { m_Aspect = aspect; };
};



extern OrthoCamera*			g_Camera2d;
extern PerspectiveCamera*	g_Camera3d;



#endif // !CAMERA_H

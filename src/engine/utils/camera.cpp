#include "camera.h"
#include "../window/window.h"

extern OrthoCamera*			g_Camera2d = 0;
extern PerspectiveCamera*	g_Camera3d = 0;


//-----------------------------------------------------------------------------------------------------
//------------------------------------------- Base Camera Class ---------------------------------------
//-----------------------------------------------------------------------------------------------------

Camera::Camera()
{
}

Camera::Camera(glm::vec3 position, glm::vec3 direction)
	: m_Position(position), m_Direction(direction)
{
}

Camera::~Camera()
{
}









//-----------------------------------------------------------------------------------------------------
//------------------------------------------- Orthographic --------------------------------------------
//-----------------------------------------------------------------------------------------------------

OrthoCamera::OrthoCamera()
	: Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	m_HorLimits[0] = -1.0f;
	m_HorLimits[1] = 1.0f;
	m_VertLimits[0] = -1.0f;
	m_VertLimits[1] = 1.0f;
	zFar = 1.0f;
	zNear = -1.0f;
	init();
}

OrthoCamera::OrthoCamera(glm::vec2 h_limits, glm::vec2 v_limits)
	: Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)), m_HorLimits(h_limits), m_VertLimits(v_limits)
{
	zFar = 1.0f;
	zNear = -1.0f;
	init();
}

OrthoCamera::OrthoCamera(glm::vec2 h_limits, glm::vec2 v_limits, float zFar, float zNear)
	: Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)), m_HorLimits(h_limits), m_VertLimits(v_limits), zFar(zFar), zNear(zNear)
{
	init();
}

OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits)
	: Camera(position, direction), m_HorLimits(h_limits), m_VertLimits(v_limits)
{
	zFar = 1.0f;
	zNear = -1.0f;
	init();
}

OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits, float zFar, float zNear)
	: Camera(position, direction), m_HorLimits(h_limits), m_VertLimits(v_limits), zFar(zFar), zNear(zNear)
{
	init();
}

OrthoCamera::OrthoCamera(float xPos, float yPos, float zPos, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits)
	: Camera(glm::vec3(xPos, yPos, zPos), direction), m_HorLimits(h_limits), m_VertLimits(v_limits)
{
	zFar = 100.0f;
	zNear = -100.0f;
	init();
}

OrthoCamera::OrthoCamera(float xPos, float yPos, float zPos, glm::vec3 direction, glm::vec2 h_limits, glm::vec2 v_limits, float zFar, float zNear)
	: Camera(glm::vec3(xPos, yPos, zPos), direction), m_HorLimits(h_limits), m_VertLimits(v_limits), zFar(zFar), zNear(zNear)
{
	init();
}

void OrthoCamera::init()
{
	m_ViewProj.view = glm::mat4(1.0f);
	m_ViewProj.perspective = glm::ortho(m_HorLimits[0], m_HorLimits[1], m_VertLimits[0], m_VertLimits[1], zNear, zFar);
}

void OrthoCamera::update()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
	m_ViewProj.view = glm::inverse(transform);
}














//-----------------------------------------------------------------------------------------------------
//------------------------------------------- Perspective ---------------------------------------------
//-----------------------------------------------------------------------------------------------------

PerspectiveCamera::PerspectiveCamera()
{}

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 direction, float fov)
	: Camera(position, direction), m_FOV(fov), m_Aspect((float)SCR_WIDTH / (float)SCR_HEIGHT), m_zNear(0.01f), m_zFar(100.0f)
{
	m_Pitch = 0.0f;
	m_Yaw = (atan2(direction.z, direction.x) * 180.0f) / (float)PI;
	update();
}

PerspectiveCamera::PerspectiveCamera(float xPos, float yPos, float zPos, glm::vec3 direction, float fov)
	: Camera(glm::vec3(xPos, yPos, zPos), direction), m_FOV(fov), m_Aspect((float)SCR_WIDTH / (float)SCR_HEIGHT), m_zNear(0.1f), m_zFar(100.0f)
{
	m_Pitch = 0.0f;
	m_Yaw = (atan2(direction.z, direction.x) * 180.0f) / (float)PI;
	update();
}

void PerspectiveCamera::update()
{
	glm::vec3 dir;
	float pitchR = glm::radians(m_Pitch);
	float yawR = glm::radians(m_Yaw);

	dir.x = cos(yawR) * cos(pitchR);
	dir.y = sin(pitchR);
	dir.z = sin(yawR) * cos(pitchR);
	//printf("\ndir = <%f, %f, %f>", dir.x, dir.y, dir.z);

	m_Direction = glm::normalize(dir);
	m_Right = glm::normalize(glm::cross(m_Direction, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Direction));

	m_ViewProj.view = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	m_ViewProj.perspective = glm::perspective(m_FOV, m_Aspect, m_zNear, m_zFar);
	//for (int i = 0; i < 4; i++)
	//{
	//	printf("\n");
	//	for (int j = 0; j < 4; j++)
	//	{
	//		printf("%f\t", m_ViewProj.perspective[j][i]);
	//		//printf("\nm[%d][%d] = %f", i, j, m[i][j]);
	//	}
	//}
	//printf("\nPosition = <%f, %f, %f>", m_Position.x, m_Position.y, m_Position.z);
}

void PerspectiveCamera::processMouseMovement(float xOffset, float yOffset)
{
	m_Yaw += xOffset;
	m_Pitch += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	// update Direction, Right and Up Vectors using the updated Euler angles
	//update();
}

#version 430 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec3 inColor;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);

//out vec4 position;
out vec3 color;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPos, 0.0, 1.0);
	//position = viewMatrix * vec4(inPos, 1.0);
	color = inColor;	
}

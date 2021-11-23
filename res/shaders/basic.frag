#version 430 core

out vec4 FragColor;

uniform vec3 light_pos;

//in vec4 position;
in vec3 color;

void main()
{
	//float intensity = 1.0 / length(fs_in.position.xyz - light_pos);
	//color = fs_in.color * intensity * 0.5;
	FragColor = vec4(color, 1.0);
}

#version 450 core

layout (location = 0) in vec3 a_Position;

out vec4 vCol;

uniform mat4 model;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * model * vec4(a_Position, 1.0f);
	vCol = vec4(clamp(a_Position, 0.0f, 1.0f), 1.0f);
}
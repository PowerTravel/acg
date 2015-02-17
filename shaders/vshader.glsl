#version  330 core

layout (location = 0) in vec3 vPosition;
uniform mat4 MV;

void main()
{
	gl_Position = MV * vec4(vPosition, 1.0f );
}

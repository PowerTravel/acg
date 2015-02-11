#version  330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 T;

void main()
{
	gl_Position =T * vec4( vPosition.x, vPosition.y, vPosition.z, 1.0f );
}

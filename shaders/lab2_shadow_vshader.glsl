#version 330 core

uniform mat4 M,V,P;

layout (location = 0) in vec3 vPositions;
layout (location = 2) in vec3 vNormal;

void main(){
	gl_Position = P*V*M*vec4(vPositions, 1);
}

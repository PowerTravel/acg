#version 330 core

layout(location=0) out vec3 fragmentDepth;

uniform mat4 M,V,P;

void main(){

	fragmentDepth.r = gl_FragCoord.z;
	fragmentDepth.g = gl_FragCoord.z;
	fragmentDepth.b = gl_FragCoord.z;
}

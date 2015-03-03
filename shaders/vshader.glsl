#version  330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 tempTex;
layout (location = 2) in vec3 vNormals;
uniform mat4 M, V, P;
varying vec2 texCoord0; 
uniform vec3 lightPosition;

varying vec3 L,E,H,N;
varying float R;

void main()
{
	texCoord0 = tempTex;
	mat4 VM = V*M;
	vec4 vp = vec4(vPosition,1);
	vec4 vn = vec4(vNormals, 0.0);

	vec4 lp = vec4(lightPosition,1);
	vec3 pos = (VM * vp).xyz;
	
	R = length( (V*lp).xyz - pos);

	L = normalize( (V*lp).xyz - pos);
	E = normalize(-pos);
	H = normalize(L+E);
	N = normalize(VM*vn).xyz;

	gl_Position = P*VM * vec4(vPosition, 1.0f );
}

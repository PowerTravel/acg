#version  330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 tempTex;
layout (location = 2) in vec3 vNormals;
uniform mat4 M, V, P;
varying vec2 texCoord0; 
uniform int nrLights;

uniform vec3 lightPosition[2];
varying vec3 L[2],E[2],H[2],N[2];
varying float R[2];
varying vec3 lip[2];

void main()
{
	texCoord0 = tempTex;
	mat4 VM = V*M;
	vec4 vp = vec4(vPosition,1);
	vec3 pos = (VM * vp).xyz;
	vec4 vn = vec4(vNormals, 0.0);

	for(int i = 0; i<nrLights; i++)
	{
		vec4 lp = vec4(lightPosition[i],1);
		R[i] = length( (V[i]*lp).xyz - pos);
		L[i] = normalize( (V[i]*lp).xyz - pos);
		E[i] = normalize(-pos);
		H[i] = normalize(L[i]+E[i]);
		N[i] = normalize(VM*vn).xyz;
	}
	lip = lightPosition;
	gl_Position = P*VM * vec4(vPosition, 1.0f );
}

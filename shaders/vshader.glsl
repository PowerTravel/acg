#version  330 core

layout (location = 0) in vec3 vPosition;
layout (location = 2) in vec3 vNormals;
uniform mat4 M, V, P;
uniform vec4 ambientProduct,diffuseProduct,specularProduct; 
uniform vec3 lightPosition;
uniform float attenuation, shininess;

out vec4 color;

void main()
{

	mat4 VM = V*M;
	vec4 vp = vec4(vPosition,1);
	vec4 vn = vec4(vNormals, 0.0);

	vec4 lp = vec4(lightPosition,1);
	vec3 pos = (VM * vp).xyz;
	
	float d = length( (V*lp).xyz - pos);

	vec3 L = normalize( (V*lp).xyz - pos);
	vec3 E = normalize(-pos);
	vec3 H = normalize(L+E);
	vec3 N = normalize(VM*vn).xyz;

	vec4 ambient = ambientProduct;

	float Kd = max(dot(L,N), 0.0);
	vec4 diffuse = Kd*diffuseProduct;
	
	if(dot(L,N) < 0.0)
	{
		diffuse = vec4(0.0,0.0,0.0,1.0);
	}

	float Ks = pow(max( dot(N,H), 0.0 ),shininess);
	vec4 specular = Ks * specularProduct;

	if( dot(L,N) < 0.0 )
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}

//	float att = 1/( 1+ attenuation*pow(d,2) );
	float att = 1; 

	color = ambient + att*(diffuse + specular);
	color.a = 1;

	gl_Position = P*VM * vec4(vPosition, 1.0f );
}

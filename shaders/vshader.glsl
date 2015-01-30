#version 300 es

in vec4 vPosition;
in vec4 vNormal;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 T;
uniform mat4 V;
uniform mat4 P;

uniform vec4 LightPosition;
uniform float Shininess;
uniform float flippNormals;

out vec4  color;

void main()
{
/*
	vec4 norm = -vec4(vNormal.xyz,0.0);
	if(flippNormals == 1)
	{
		norm = -norm;
	}

	mat4 ModelView = V*T;
	vec3 pos = (ModelView*vPosition).xyz;
	
	vec3 L = normalize( (V*LightPosition).xyz - pos );
	vec3 E = normalize( -pos );
	vec3 H = normalize( L+E );
	vec3 N = normalize( ModelView*norm).xyz;

	vec4 ambient = AmbientProduct;

	float Kd = max( dot(L,N), 0.0 );
	vec4 diffuse = Kd*DiffuseProduct;
*/
/*	
	if(dot(L,N) < 0.0)
	{
		diffuse = vec4(0.0,0.0,0.0,1.0);
	}
*/
/*	
	float Ks = pow( max( dot(N,H), 0.0 ) , Shininess);
	vec4 specular = Ks * SpecularProduct;
	
	if( dot(L,N) < 0.0 )
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}
	
	gl_Position = P*ModelView*vPosition;
	
	color = ambient + diffuse + specular;
	color.a = 1.0;
*/	
//	color = vec4( cos(-(V*T*vPosition).x*2)+1, sin(	(V*T*vPosition).y*2)+1, cos((V*T*vPosition).z*2)*sin((V*T*vPosition).y*2), 1.0 );	
//	color = vec4( cos(-vPosition.x*10)+1, sin(	vPosition.y*10)+1, cos(	vPosition.z*10)*sin(vPosition.y*10), 1.0 );	
//	color = vec4( cos(-pos.x*2)+1, sin(pos.y*2)+1, cos(pos.z*2)*sin(pos.y*2), 1.0 );
}

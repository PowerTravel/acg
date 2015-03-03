#version 330 core
out vec4 fragColor;

uniform vec4 ambientProduct,diffuseProduct,specularProduct; 
uniform float attenuation, shininess,usingTexture;
uniform sampler2D gSampler;

varying vec3 L,E,H,N;
varying vec2 texCoord0; 
varying float R;


void main() 
{ 
	vec4 ambient, diffuse, specular;
	
	ambient = ambientProduct;

	float Kd = max(dot(L,N), 0.0);
	if(usingTexture != 0.f)
	{
		//diffuse = Kd*texture2D(gSampler,texCoord0.st)*diffuseProduct;
		// Replace the diffuse term with our texture if that is what we have
		diffuse = Kd*texture2D(gSampler,texCoord0.st);
	}else{
		diffuse = Kd*diffuseProduct;
	}


	float Ks = pow(max( dot(N,H), 0.0 ),shininess);
	specular = Ks * specularProduct;


	if(dot(L,N) < 0.0)
	{
		diffuse = vec4(0.0,0.0,0.0,1.0);
	}
	if( dot(L,N) < 0.0 )
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}
	
//	float att = 1/( 1+ attenuation*pow(R,2) );
	float att = 1/( 1+ 0.01*pow(R,2) );

	fragColor = ambient+att*(diffuse+specular);
}

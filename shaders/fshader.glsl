#version 330 core
out vec4 fragColor;

uniform vec4 ambientProduct[3],diffuseProduct[3],specularProduct[3]; 
uniform float attenuation[3];
uniform float shininess;
uniform int usingTexture,nrLights;
uniform sampler2D gSampler;

varying vec3 L[3],E[3],H[3],N[3];
varying float R[3];
varying vec2 texCoord0; 

void main() 
{ 

	vec4 color = vec4(0,0,0,0);
	for(int i = 0; i<nrLights; i++)
	{
		vec4 ambient, diffuse, specular;
		
		ambient = ambientProduct[i];

		float Kd = max(dot(L[i],N[i]), 0.0);
		if(usingTexture != 0.f)
		{
			diffuse = Kd*texture2D(gSampler,texCoord0.st);
		}else{
			diffuse = Kd*diffuseProduct[i];
		}

		float Ks = pow(max( dot(N[i],H[i]), 0.0 ), shininess);
		specular = Ks * specularProduct[i];


		if(dot(L[i],N[i]) < 0.0)
		{
			diffuse = vec4(0.0,0.0,0.0,1.0);
			specular = vec4(0.0, 0.0, 0.0, 1.0);
		}
	
		float att = 1/( 1 + attenuation[i]*pow(R[i],2) );

		color += ambient+att*(diffuse+specular);
	}

	fragColor = color;
}

#version 330 core
out vec4 fragColor;

uniform vec4 ambientProduct[2],diffuseProduct[2],specularProduct[2]; 
uniform float attenuation[2], shininess[2];
uniform int usingTexture;
uniform sampler2D gSampler;

varying vec3 L[2],E[2],H[2],N[2];
varying float R[2];
varying vec2 texCoord0; 
uniform int nrLights;

varying vec3 lip[2];

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
			//diffuse = Kd*texture2D(gSampler,texCoord0.st)*diffuseProduct;
			// Replace the diffuse term with our texture if that is what we have
			diffuse = Kd*texture2D(gSampler,texCoord0.st);
		}else{
			diffuse = Kd*diffuseProduct[i];
		}

		//float Ks = pow(max( dot(N[i],H[i]), 0.0 ), shininess[i]);
		float Ks = pow(max( dot(N[i],H[i]), 0.0 ), 1000);
		specular = Ks * specularProduct[i];


		if(dot(L[i],N[i]) < 0.0)
		{
			//diffuse = vec4(0.0,0.0,0.0,1.0);
		}
		if( dot(L[i],N[i]) < 0.0 )
		{
			//specular = vec4(0.0, 0.0, 0.0, 1.0);
		}
	
//	float att = 1/( 1+ attenuation*pow(R,2) );
		float att = 1/( 1+ 0.005*pow(R[i],2) );
		att = 1;	
		color +=ambient+att*(diffuse+specular);
	}

	fragColor = color;
	//if(lip[0] == vec3(0,1,2) &&
	//	lip[1] == vec3(3,4,5)){
	//	fragColor = vec4(0.5, 0,0,1);
	//}
}

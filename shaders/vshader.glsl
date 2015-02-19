#version  330 core

layout (location = 0) in vec3 vPosition;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 color;

void main()
{

	mat4 PVM = P*V*M;
//	mat4 PVM = M;

	// To  be sent as uniforms later:
	//vec3 position = vec3(4,4,4);
	//vec4 ambient = vec4(0.1,0.02,0.1,1);
	//vec4 diffuse = vec4(0.4,0.3,0.5,1);
	//vec4 specular = vec4(0.6,0.8,0.3);
	
	//Vec4 vertPos = vec4(vPosition, 1.0f );
	//vec3 pos = (ModelView * vPosition).xyz;

	


	color = vec4(0.4, 0.8, 0.3, 1);
	gl_Position = PVM * vec4(vPosition, 1.0f );
}

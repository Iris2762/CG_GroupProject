#version 330 core

layout (location = 0) in vec3 aPos;//vertex pos
layout(location=1) in vec2 aTexCoord;// vertex texture
//layout (location = 2) in vec3 Normal;

struct Light {
	vec4 ambientProduct;
	vec4 diffuseProduct;
	vec4 specularProduct;
	vec4 LightPosition;
	float Shininess;
};
uniform vec3 pos;//ball center pos
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform Light lights[3];

out vec4 color;
out vec2 st;
void main()
{
	vec3 result=vec3(0,0,0);
	gl_Position=proj * view * model * vec4(aPos, 1.0);
	for(int i=0;i<3;i++){
	vec4 ambient,diffuse,specular;
   	vec3 N=aPos-lights[i].LightPosition.xyz;
   	N=normalize(N.xyz);
   	vec3 L=normalize(lights[i].LightPosition.xyz-(view * model * vec4(aPos, 1.0)).xyz);
   	vec3 E=-normalize((view * model * vec4(aPos, 1.0)).xyz);
   	vec3 H=normalize(L+E);
   	float Kd=max(dot(L,N),0.0);
   	float Ks=pow(max(dot(N,H),0.0),lights[i].Shininess);
   	ambient=lights[i].ambientProduct;

   	diffuse=Kd*lights[i].diffuseProduct;
   	specular = max(pow(max(dot(N, H), 0.0), lights[i].Shininess) * lights[i].specularProduct, 0.0);
   	vec3 color_i=(ambient+diffuse+specular).xyz;
	result+=color_i;
	}
	//归一化，避免多个光源效果叠加导致rgb超过1
	if(result.x>1)result.x=1;
	if(result.y>1)result.y=1;
	if(result.z>1)result.z=1;
   	color=vec4(result,1);
   	st = aTexCoord;
}
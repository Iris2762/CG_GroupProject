#version 330 core

layout (location = 0) in vec3 aPos;
layout(location=1) in vec2 aTexCoord;
//layout (location = 2) in vec3 Normal;
//layout (location = 1) in vec3 Normal;

out vec4 color;
out vec2 st;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;
uniform vec3 pos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
  //color=vec4(1.0f,0.0f,0.0f,1.0f);
   vec4 ambient,diffuse,specular;
   gl_Position=proj * view * model * vec4(aPos, 1.0);
   vec3 N=aPos-pos;//法向量随球心位置改变而改变
   N=normalize(N.xyz);
   vec3 L=normalize(LightPosition.xyz-(view * model * vec4(aPos, 1.0)).xyz);
   vec3 E=-normalize((view * model * vec4(aPos, 1.0)).xyz);
   vec3 H=normalize(L+E);
   float Kd=max(dot(L,N),0.0);
   float Ks=pow(max(dot(N,H),0.0),Shininess);
   ambient=ambientProduct;
   diffuse=Kd*diffuseProduct;
   specular = max(pow(max(dot(N, H), 0.0), Shininess) * specularProduct, 0.0);
   color=vec4((ambient+diffuse+specular).xyz,1.0);

   st = aTexCoord;
}
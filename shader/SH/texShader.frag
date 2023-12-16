#version 330 core
out vec4 FragColor;

// 纹理坐标是3维的
in vec2 TexCoords;// 纹理坐标

// 天空盒纹理采样
uniform sampler2D skybox;

void main(){ 
   vec2 st=TexCoords.xy;
    FragColor = texture2D(skybox,st);
}

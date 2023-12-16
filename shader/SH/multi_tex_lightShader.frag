#version 330 core

in vec2 st;
in vec4 color;
uniform sampler2D texMap;

//out vec4 FragColor;

const int density = 4;

void main()
{
	gl_FragColor=color*texture2D(texMap,st);
}
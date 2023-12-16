#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 color;

void main()
{
	if(((int(TexCoord.x * 4) + int(TexCoord.y * 4)) & 0x1) != 0)
		FragColor = color;
	else
		FragColor = color + vec4(0.1f, 0.1f, 0.1f, 0.0f);
}
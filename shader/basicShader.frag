#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

const int density = 4;

void main()
{
	if(((int(TexCoord.x * density) + int(TexCoord.y * density)) & 0x1) != 0)
		FragColor = vec4(0.7333f, 0.87f, 1.0f, 1.0f);
	else
		FragColor = vec4(0.6333f, 0.77f, 0.9f, 1.0f);
}
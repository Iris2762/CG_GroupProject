#version 330 core

out vec4 FragColor;

void main()
{
    float px = gl_PointCoord.x - 0.5;
    float py = gl_PointCoord.y - 0.5;
	if(sqrt(px*px+py*py) <= 0.25) {
        FragColor = vec4(0.7333f, 0.87f, 1.0f, 1.0f);
    } else {
        discard;
    }
}
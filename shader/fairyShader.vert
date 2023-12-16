#version 330 core

layout (location = 0) in vec3 aPos;

// TODO
// view + model = viewModel
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
// uniform float radius;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
    // TODO
    // point size should be calculated to match radius
    gl_PointSize = 100.0;
}
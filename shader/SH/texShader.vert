#version 330 core
layout (location = 0) in vec3 aPos;
layout(location=1) in vec2 aTexCoord;

// 纹理坐标是3维的
out vec2 TexCoords;

// 不用model转换到世界矩阵
uniform mat4 proj;
uniform mat4 view;
void main()
{
    // 纹理坐标等于位置坐标/
    TexCoords =aTexCoord;

    vec4 pos = proj * view * vec4(aPos, 1.0);
    // z为w，透视除法除后z=(z=w/w)=1，深度为最远///
 gl_Position = pos.xyww;
   //gl_Position = pos;
}

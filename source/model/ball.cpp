#include <vector>
#include "helper.h"
#include "model/ball.h"
int rotateAngle = 0;

#define X .525731112119133606f
#define Z .850650808352039932f

static glm::vec3 v[12] = {
    { -X, 0.0f,   Z }, {  X, 0.0f,   Z }, { -X, 0.0f,  -Z }, {  X, 0.0f,  -Z },
    {0.0f,   Z,   X }, {0.0f,   Z,  -X }, {0.0f,  -Z,   X }, {0.0f,  -Z,  -X },
    {  Z,   X, 0.0f }, { -Z,   X, 0.0f }, {  Z,  -X, 0.0f }, { -Z,  -X, 0.0f }
};

static GLuint tindices[20][3] = {
    {1, 4, 0},{ 4,9,0}, {4, 5,9}, {8,5, 4}, { 1,8,4},
    {1,10, 8},{10,3,8}, {8, 3,5}, {3,2, 5}, { 3,7,2},
    {3,10, 7},{10,6,7}, {6,11,7}, {6,0,11}, { 6,1,0},
    {10,1, 6},{11,0,9}, {2,11,9}, {5,2, 9}, {11,2,7}
};

std::vector<glm::vec3> vdata;



Ball::Ball(const std::string& name, float radius): VerticeNum(0){
    _shader.textureID = loadTexture(name);//读取纹理
   tetrahedron(6);
   set_radius(radius);
   _mesh.update_buffer();
}

void Ball::set_radius(float radius_new) {
    for (int i = 0; i < this->_mesh.vertices.size(); i++) {
        this->_mesh.vertices[i] *= radius_new / this->radius;
    }
    this->radius = radius_new;
}

float Ball::get_radius() {
    return this ->radius;
}

void Ball::tetrahedron(int n) {
    for (int i = 0; i < 20; ++i) {
        divide_triangle(v[tindices[i][0]], v[tindices[i][1]], v[tindices[i][2]], n);
    }
}

void Ball::divide_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int n) {
    glm::vec3 v1, v2, v3;
    if (n > 0) {
        // 如果使用归一化，顶点和的结果是否除以 2 都不影响结果
        v1 = (a + b);
        v2 = (a + c);
        v3 = (b + c);

        // 归一化 的坐标贴近球面。但如果不进行归一化，显示的就是一个细分的四面体
        v1 = glm::normalize(v1);
        v2 = glm::normalize(v2);
        v3 = glm::normalize(v3);

        divide_triangle(a, v2, v1, n - 1);
        divide_triangle(c, v3, v2, n - 1);
        divide_triangle(b, v1, v3, n - 1);
        divide_triangle(v1, v2, v3, n - 1);
        // 递归细分相邻的三角形
        divide_triangle(v1, b, v3, n - 1);
        divide_triangle(v2, c, v1, n - 1);
    }
    else
        triangle(a, b, c);
}



void Ball::triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    this->_mesh.vertices.emplace_back(a[0]);
    this->_mesh.vertices.emplace_back(a[1]);
    this->_mesh.vertices.emplace_back(a[2]);
    this->_mesh.vertices.emplace_back(b[0]);
    this->_mesh.vertices.emplace_back(b[1]);
    this->_mesh.vertices.emplace_back(b[2]);
    this->_mesh.vertices.emplace_back(c[0]);
    this->_mesh.vertices.emplace_back(c[1]);
    this->_mesh.vertices.emplace_back(c[2]);
    // 计算纹理坐标
    glm::vec2 uv_a = sphericalToTextureCoord(a);
    glm::vec2 uv_b = sphericalToTextureCoord(b);
    glm::vec2 uv_c = sphericalToTextureCoord(c);
    this->_mesh.textureCoord.emplace_back(uv_a[0] > 0.5 ? 1 - uv_a[0] : uv_a[0]);
    //this->_mesh.textureCoord.emplace_back(uv_a[1] > 0.5 ? 1 - uv_a[1] : uv_a[1]);
    this->_mesh.textureCoord.emplace_back(uv_a[1]);
    this->_mesh.textureCoord.emplace_back(uv_b[0] > 0.5 ? 1 - uv_b[0] : uv_b[0]);
    //this->_mesh.textureCoord.emplace_back(uv_b[1] > 0.5 ? 1 - uv_b[1] : uv_b[1]);
    this->_mesh.textureCoord.emplace_back(uv_b[1]);
    this->_mesh.textureCoord.emplace_back(uv_c[0] > 0.5 ? 1 - uv_c[0] : uv_c[0]);
    // this->_mesh.textureCoord.emplace_back(uv_c[1] > 0.5 ? 1 - uv_c[1] : uv_c[1]);
    this->_mesh.textureCoord.emplace_back(uv_c[1]);
    for (int i = 0; i < 9; i++) {
        this->_mesh.indices.emplace_back(VerticeNum+i);
    }
    VerticeNum += 9;
}
glm::vec2 Ball::sphericalToTextureCoord(glm::vec3 point) {
    float u = 0.5f + atan2(point.z, point.x) / (2.0f * glm::pi<float>());
    float v = 0.5f - asin(point.y) / glm::pi<float>();
    return glm::vec2(u, v);
}
void Ball::render(glm::mat4 viewMat, glm::mat4 projMat) {
        auto modelMat = getTransMat();
        //give ball pos
        _shader.render(_mesh, modelMat, viewMat, projMat, _position);
}

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    createTriangleMesh(_mesh, a, b, c);
    _mesh.update_buffer();
}

void Triangle::render(glm::mat4 viewMat, glm::mat4 projMat) {
    auto modelMat = getTransMat();
    _shader.render(_mesh, modelMat, viewMat, projMat);
}

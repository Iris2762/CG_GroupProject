#ifndef BALL_H
#define BALL_H

#include "model/model.h"
#include "shader/meshShader.h"
#include "shape.h"

class Triangle:public Model {
public:
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    virtual void render(glm::mat4 viewMat, glm::mat4 projMat);

private:
    GLuint VAO;
    Mesh _mesh;
    MeshShader _shader;
};

class Ball:public Model
{
public:
    //add name to load texture
    Ball(const std::string& name, float radius = 1);
    virtual void render(glm::mat4 viewMat, glm::mat4 projMat);
    void set_radius(float radius);
    float get_radius();
    
private:
    void tetrahedron(int n);
    void divide_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int n);
    void triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    //calculate texture pos
    glm::vec2 Ball::sphericalToTextureCoord(glm::vec3 point);
    float radius=1;
    int VerticeNum;
    GLuint VAO;
    Mesh _mesh;
    MeshShader _shader;
};

#endif
#ifndef MESH_SHADER_H
#define MESH_SHADER_H

#include "shader/shader.h"
#include "mesh.h"
#include <string>
// A MeshShader takes in mesh and render it
class MeshShader
{
public:
    MeshShader();
    //_pos is ball center position
    virtual void render(Mesh &mesh, glm::mat4 &modelMat, glm::mat4 &viewMat, glm::mat4 &projMat,glm::vec3 _pos=glm::vec3(0.0f,0.0f,0.0f)) const;
    //a function to set light param
    void setLightParam(std::string p_name, int index=-1,glm::vec4 v1 = glm::vec4(0, 0, 0, 0), float v2 = 0.0f);
    //texture param
    unsigned int textureID;
    //设置光照参数(已设置初始化值，如需修改，则调用updateShape
    // 3 point lights
    glm::vec4 light_position[3];
    glm::vec4 light_ambient[3];
    glm::vec4 light_diffuse[3];
    glm::vec4 light_specular[3];
    glm::vec4 cube_mat_ambient;
    glm::vec4 cube_mat_diffuse;
    glm::vec4 cube_mat_specular;
    glm::vec4 cube_mat_emission;
    float cube_mat_shininess;

private:
    static bool is_built;
    static GLuint ID;
    
};
//boxshader is only for skybox
class boxShader
{
public:
    boxShader();
    virtual void render(Mesh& mesh,  glm::mat4& viewMat, glm::mat4& projMat) const;
    //texture param
    unsigned int textureID;

private:
    static bool is_built;
    static GLuint ID;

};

#endif
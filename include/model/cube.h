#ifndef CUBE_H
#define CUBE_H

#include "model/model.h"
#include "shader/meshShader.h"
#include<vector>
class Cube : public Model
{
public:
    //used as skybox
    Cube(const std::string& name, float size = 2);
    virtual void render(glm::mat4 viewMat, glm::mat4 projMat);

private:
    Mesh _mesh;
    boxShader _shader;
    //MeshShader _shader;
};
void createCube(Mesh& _mesh, const float size);
#endif
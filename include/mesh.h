#ifndef MESH_H
#define MESH_H

#include "helper.h"
#include <vector>

// Mesh stores vertices, indices and texture coord
// independent triangle shading assumed,
// no edge or face information provided
// TODO: Add vertex attri
class Mesh {
public:
    Mesh();
    ~Mesh();
    void update_buffer();
    GLuint get_VAO() const;
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    std::vector<float> textureCoord;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

void createCubeMesh(Mesh &mesh, const float size);
void createTriangleMesh(Mesh& mesh, glm::vec3 a, glm::vec3 b, glm::vec3 c);

#endif
#ifndef SHAPE_H
#define SHAPE_H

#include "helper.h"
#include <vector>

// Shape stores vertices, indices and texture coord
// * Ideally, this shuold be more abstract.
// * But auto triangulation and UV mapping is required, which is comlicated.
// * So I assume you have done these somewhere else.
class Shape {
public:
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    std::vector<float> textureCoord;
};

void createCubeShape(Shape &shape, const float size);


void createTriangleShape(Shape& shape, glm::vec3 a, glm::vec3 b, glm::vec3 c);
#endif
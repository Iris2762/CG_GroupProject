#ifndef FAIRY_H
#define FAIRY_H

#include "model.h"
#include "shader/fairyShader.h"
#include <vector>

// A Fairy is a glowing partical in scene
class Fairy : public Model {
public:
    Fairy();
    ~Fairy();
    // I am too lazy to implement interface
    std::vector<glm::vec3> pos;
    // use this after you update pos
    void update();

    virtual void render(glm::mat4 viewMat, glm::mat4 projMat);

private:
    FairyShader _shader;
    GLuint VBO;
    GLuint VAO;
};

#endif
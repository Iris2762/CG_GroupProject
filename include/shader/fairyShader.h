#ifndef FAIRY_SHADER_H
#define FAIRY_SHADER_H

#include "shader.h"
#include <vector>

// FairyShader renders glowing particals
class FairyShader
{
public:
    FairyShader();
    void render(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, GLuint VAO, int num) const;

private:
    static bool is_built;
    static GLuint ID;
};

#endif
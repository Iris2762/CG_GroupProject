#ifndef SHADER_H
#define SHADER_H

#include "helper.h"
#include "shape.h"
//only read shader code
GLuint load_shader(const std::string& vertexPath, const std::string& fragmentPath);

#endif
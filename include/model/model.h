#ifndef MODEL_H
#define MODEL_H

#include "object.h"

// A model is an object that can be rendered.
class Model: public Object {
public:
    // render function
    virtual void render(glm::mat4 viewMat, glm::mat4 projMat) = 0;
};

#endif
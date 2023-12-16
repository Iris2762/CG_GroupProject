#ifndef OBJECT_H
#define OBJECT_H

#include "helper.h"
#include "shader/shader.h"

// The object includes
// world class position, scale and rotation
class Object {
public:
    // default with position=(0,0,0), scale=1, rotation=0

    Object();
    Object(const glm::vec3 position, const float scale, const float rotation);

    // setter

    void setPosition(const glm::vec3 position);
    void setScale(const glm::vec3 scale);
    void setRotation(const glm::mat4 rotation);
    void reset(const bool resetPos, const bool resetSca, const bool resetRot);

    // alter

    void shift(const glm::vec3 shift);
    void scale(const float scale);
    void rotate(const glm::mat4 rotation);

    // getter

    glm::vec3 getPosition() const;
    glm::vec3 getScale() const;
    glm::mat4 getRotation() const;
    glm::mat4 getTransMat() const;
protected:

    glm::vec3 _position;
    glm::vec3 _scale;
    glm::mat4 _rotation;
};

#endif
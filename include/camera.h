#ifndef CAMERA_H
#define CAMERA_H

#include "helper.h"
#include "object.h"

// The Camera takes care of the status and manipulations of camera
class Camera: public Object {
public:
    Camera();
    
    // positio fix, camera holding up
    void aimAt(glm::vec3 target);

    void setOrtho(float width, float height, float nearD, float farD);
    void setPersp(float fov, float width, float height, float nearD, float farD);
    void resize(float width, float height);

    glm::mat4 getView() const;
    glm::mat4 getProj() const;
private:
    glm::mat4 projMat;
    bool _isPerp;
    float _nearD;
    float _farD;
    float _fov;
};

#endif
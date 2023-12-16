#include "camera.h"

Camera::Camera() {
    _isPerp = true;
    setPersp(glm::radians(45.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 0.1f, 100.0f);
}

void Camera::aimAt(glm::vec3 target) {
    if(target == _position) return;
    auto cameraDirection = glm::normalize(_position - target);
    glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f); 
    if(cameraDirection == glm::vec3(0.0f, 0.0f, 1.0f)) {
        _rotation = glm::mat4(1.0f);
        return;
    }
    if(cameraDirection == glm::vec3(0.0f, 0.0f, -1.0f)) {
        _rotation = glm::mat4(1.0f);
        _rotation[2][2] = -1; 
        return;
    }
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    _rotation = glm::mat4(1.0f);
    _rotation[0] = glm::vec4(cameraRight, 0.0f);
    _rotation[1] = glm::vec4(cameraUp, 0.0f);
    _rotation[2] = glm::vec4(cameraDirection, 0.0f);
}

void Camera::setOrtho(float width, float height, float nearD, float farD) {
    _isPerp = false;
    _nearD = nearD;
    _farD = farD;
    projMat = glm::ortho(-width / 2, width / 2,
        -height / 2, height / 2,
        nearD, farD);
}

void Camera::setPersp(float fov, float width, float height, float nearD, float farD) {
    _isPerp = true;
    _fov = fov;
    _nearD = nearD;
    _farD = farD;
    projMat = glm::perspective(
        fov, width / height, nearD, farD
    );
}

void Camera::resize(float width, float height) {
    if(_isPerp) {
        setPersp(_fov, width, height, _nearD, _farD);
    } else {
        setOrtho(width, height, _nearD, _farD);
    }
}

glm::mat4 Camera::getView() const {
    auto iposition = glm::inverse(glm::translate(glm::mat4(1.0f), _position));
    auto irotation = glm::inverse(_rotation);
    auto A = irotation * iposition;
    auto B = glm::inverse(getTransMat());
    return irotation * iposition;
}

glm::mat4 Camera::getProj() const {
    return projMat;
}
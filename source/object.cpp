#include "object.h"

Object::Object(): 
    _position(glm::vec3(0, 0, 0)),
    _scale(glm::vec3(1.0f)),
    _rotation(glm::mat4(1.0f)) {

}

Object::Object(const glm::vec3 position, const float scale, const float rotation):
    _position(position),
    _scale(scale),
    _rotation(rotation) {

}

void Object::setPosition(const glm::vec3 position) {
    this->_position = position;
}

void Object::setScale(const glm::vec3 scale) {
    this->_scale = scale;
}

void Object::setRotation(const glm::mat4 rotation) {
    this->_rotation = rotation;
}

void Object::reset(const bool resetPos, const bool resetSca, const bool resetRot) {
    if(resetPos) this->_position = glm::vec3(0, 0, 0);
    if(resetSca) this->_scale = glm::vec3(1.0f);
    if(resetRot) this->_rotation = glm::mat4(1.0f);
}

void Object::shift(const glm::vec3 shift) {
    this->_position += shift;
}

void Object::scale(const float scale) {
    this->_scale *= scale;
}

void Object::rotate(const glm::mat4 rotation) {
    this->_rotation = rotation * this->_rotation;
}

glm::vec3 Object::getPosition() const {
    return this->_position;
}

glm::vec3 Object::getScale() const {
    return this->_scale;
}

glm::mat4 Object::getRotation() const {
    return this->_rotation;
}

glm::mat4 Object::getTransMat() const {
    auto transMat = glm::mat4(1.0f);
    transMat = glm::scale(transMat, _scale);
    transMat = _rotation * transMat;
    transMat = glm::translate(glm::mat4(1.0f), _position) * transMat;
    return transMat;
}
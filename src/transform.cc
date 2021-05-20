#include "include/transform.h"

Transform::Transform() {
    model = glm::mat4(1.0f);
}
void Transform::Translate(float unitsX, float unitsY, float unitsZ) {
    model = glm::translate(model, glm::vec3(unitsX, unitsY, unitsY));
}

void Transform::Translate(glm::vec3 units) {
    model = glm::translate(model, units);
}
void Transform::Rotate(float degrees, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(degrees), axis);
}
void Transform::Scale(float scaleX, float scaleY, float scaleZ) {
    model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
}

void Transform::Scale(glm::vec3 scale) {
    model = glm::scale(model, scale);
}
void Transform::Reset() {
    model = glm::mat4(1.0f);
}
glm::mat4 Transform::GetModel() {
    return model;
}
Transform::~Transform() {
}
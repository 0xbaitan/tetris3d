#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef TRANSFORM_IMPLEMENTATION_H
#define TRANSFORM_IMPLEMENTATION_H 1

class Transform {
    public:
    Transform();
   void Translate(float unitsX, float unitsY, float unitsZ);
   void Translate(glm::vec3 units);
   void Rotate(float degrees, glm::vec3 axis);
   void Scale(float scaleX, float scaleY, float scaleZ);
   void Scale(glm::vec3 scale);
   void Reset();
   glm::mat4 GetModel();
    ~Transform();
    private:
    glm::mat4 model;
};

#endif


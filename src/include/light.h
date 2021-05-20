#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader.h"
#include "shadow.h"

#ifndef LIGHT_IMPLEMENTATION
#define LIGHT_IMPLEMENTATION 1

struct Light {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};
struct DirectionalLight : Light {

    glm::vec3 direction;
    float near_plane;
    float far_plane;
    float size_neg_x, size_pos_x, size_neg_y, size_pos_y;
    DirectionalLight(glm::vec3 v_ambient, glm::vec3 v_diffuse, glm::vec3 v_specular, glm::vec3 v_direction);

    void SetLightSpaceMatrixAttrib(float v_near_plane, float v_far_plane, float v_size_neg_x, float v_size_pos_x, float v_size_neg_y, float v_size_pos_y);

    glm::mat4 GetLightSpaceMatrix();

    void SetAttributes(Shader *shader, unsigned int index);

    void SetLightSpaceMatrix(Shader *shader);
};
struct PointLight : Light {

    glm::vec3 pos;
    float constant, linear, quadratic;
    float near_plane;
    float far_plane;
    float aspect;
    float shadowHeight, shadowWidth;
    PointShadow* shadow;
    PointLight(glm::vec3 v_ambient, glm::vec3 v_diffuse, glm::vec3 v_specular, glm::vec3 v_pos,
               float v_constant, float v_linear, float v_quadratic, float v_near_plane, float v_far_plane,
               float v_aspect, float shadowHeight, float shadowWidth);

    void SetAttributes(Shader *shader, unsigned int index);

    void SetShadowAttributes(Shader *shader, unsigned int index);

    PointShadow* GetShadow();

    void SetLightSpaceMatrix(Shader *shader);
};
struct SpotLight : PointLight {

    glm::vec3 direction;
    float cutoff;
    float outer_cutoff;

    SpotLight(glm::vec3 v_ambient, glm::vec3 v_diffuse, glm::vec3 v_specular, glm::vec3 v_pos, glm::vec3 v_direction,
              float v_constant, float v_linear, float v_quadratic, float v_near_plane, float v_far_plane,
              float v_aspect, float shadowHeight, float shadowWidth, float v_cutoff, float v_outer_cutoff);

    void SetAttributes(Shader *shader, unsigned int index);
};

#endif
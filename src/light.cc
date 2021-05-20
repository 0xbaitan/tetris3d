#include "include/light.h"

/* --- Members of Light Struct ----*/

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

/* --- Members of Directional Light Struct ----*/

DirectionalLight::DirectionalLight(glm::vec3 v_ambient, glm::vec3 v_diffuse, glm::vec3 v_specular, glm::vec3 direction) : Light(v_ambient, v_diffuse, v_specular) {
    this->direction = direction;
}

void DirectionalLight::SetAttributes(Shader *shader, unsigned int index) {
    char localBuff[100] = {'\0'};

    snprintf(localBuff, sizeof(localBuff), "directionalLights[%d].base.ambient", index);
    shader->SetUniform(localBuff, ambient);

    snprintf(localBuff, sizeof(localBuff), "directionalLights[%d].base.diffuse", index);
    shader->SetUniform(localBuff, diffuse);

    snprintf(localBuff, sizeof(localBuff), "directionalLights[%d].base.specular", index);
    shader->SetUniform(localBuff, specular);

    snprintf(localBuff, sizeof(localBuff), "directionalLights[%d].direction", index);
    shader->SetUniform(localBuff, direction);
}

void DirectionalLight::SetLightSpaceMatrixAttrib(float v_near_plane, float v_far_plane, float v_size_neg_x, float v_size_pos_x, float v_size_neg_y, float v_size_pos_y) {
    this->near_plane = v_near_plane;
    this->far_plane = v_far_plane;
    this->size_neg_x = v_size_neg_x;
    this->size_pos_x = v_size_pos_x;
    this->size_neg_y = v_size_neg_y;
    this->size_pos_y = v_size_pos_y;
}

void DirectionalLight::SetLightSpaceMatrix(Shader *shader) {
    glm::mat4 light_projection = glm::ortho(size_neg_x, size_pos_x, size_neg_y, size_pos_y, near_plane, far_plane);
    glm::mat4 light_view = glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader->SetUniform("light_space_matrix", light_projection * light_view);
}

PointLight::PointLight(glm::vec3 v_ambient, glm::vec3 v_diffuse, glm::vec3 v_specular, glm::vec3 v_pos, float v_constant, float v_linear, float v_quadratic, float v_near_plane, float v_far_plane, float v_aspect, float shadowHeight, float shadowWidth) : Light(v_ambient, v_diffuse, v_specular) {
    this->pos = v_pos;
    this->constant = v_constant;
    this->linear = v_linear;
    this->quadratic = v_quadratic;
    this->near_plane = v_near_plane;
    this->far_plane = v_far_plane;
    this->aspect = v_aspect;
    this->shadowHeight = shadowHeight;
    this->shadowWidth = shadowWidth;
    shadow = new PointShadow(shadowHeight, shadowWidth);
    shadow->CreateShadowMap();
}

void PointLight::SetAttributes(Shader *shader, unsigned int index) {
    char localBuff[100] = {'\0'};

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].base.ambient", index);
    shader->SetUniform(localBuff, ambient);

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].base.diffuse", index);
    shader->SetUniform(localBuff, diffuse);

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].base.specular", index);
    shader->SetUniform(localBuff, specular);

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].pos", index);
    shader->SetUniform(localBuff, pos);

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].constant", index);
    shader->SetUniform(localBuff, constant);

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].linear", index);
    shader->SetUniform(localBuff, linear);

    snprintf(localBuff, sizeof(localBuff), "pointLights[%d].quadratic", index);
    shader->SetUniform(localBuff, quadratic);
}

 void PointLight::SetShadowAttributes(Shader *shader, unsigned int index) {
     char localBuff[100] = {'\0'};

    snprintf(localBuff, sizeof(localBuff), "pointShadows[%d].farPlane", index);
    shader->SetUniform(localBuff, far_plane);

    shadow->Read(GL_TEXTURE15);
    snprintf(localBuff, sizeof(localBuff), "pointShadows[%d].shadowCube", index);
    shader->SetUniform(localBuff, 15);
 }

PointShadow* PointLight::GetShadow() {
    return shadow;
}

void PointLight::SetLightSpaceMatrix(Shader *shader) {
    glm::mat4 light_projection = glm::perspective(glm::radians(90.0f), aspect, near_plane, far_plane);

    std::vector<glm::mat4> shadow_transforms;
    shadow_transforms.push_back(light_projection * (glm::lookAt(pos, pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f))));
    shadow_transforms.push_back(light_projection * (glm::lookAt(pos, pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f))));
    shadow_transforms.push_back(light_projection * (glm::lookAt(pos, pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))));
    shadow_transforms.push_back(light_projection * (glm::lookAt(pos, pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f))));
    shadow_transforms.push_back(light_projection * (glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f))));
    shadow_transforms.push_back(light_projection * (glm::lookAt(pos, pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))));

    char localBuff[100] = {'\0'};

    for (unsigned int face = 0; face < shadow_transforms.size(); face++) {
        snprintf(localBuff, sizeof(localBuff), "shadowMatrices[%d]", face);
        shader->SetUniform(localBuff, shadow_transforms[face]);
    }
}

SpotLight::SpotLight(glm::vec3 v_ambient, glm::vec3 v_diffuse, glm::vec3 v_specular, glm::vec3 v_pos, glm::vec3 v_direction,
                     float v_constant, float v_linear, float v_quadratic, float v_near_plane, float v_far_plane, float v_aspect, float shadowHeight, float shadowWidth,
                     float v_cutoff, float v_outer_cutoff)
    : PointLight(v_ambient, v_diffuse, v_specular, v_pos, v_constant, v_linear, v_quadratic, v_near_plane, v_far_plane, v_aspect, shadowHeight, shadowWidth) {

    this->direction = v_direction;
    this->cutoff = glm::cos(glm::radians(v_cutoff));
    this->outer_cutoff = glm::cos(glm::radians(v_outer_cutoff));
}

void SpotLight::SetAttributes(Shader *shader, unsigned int index) {
    char localBuff[100] = {'\0'};

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.base.ambient", index);
    shader->SetUniform(localBuff, ambient);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.base.diffuse", index);
    shader->SetUniform(localBuff, diffuse);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.base.specular", index);
    shader->SetUniform(localBuff, specular);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.pos", index);
    shader->SetUniform(localBuff, pos);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.constant", index);
    shader->SetUniform(localBuff, constant);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.linear", index);
    shader->SetUniform(localBuff, linear);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].p_base.quadratic", index);
    shader->SetUniform(localBuff, quadratic);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].direction", index);
    shader->SetUniform(localBuff, direction);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].cutoff", index);
    shader->SetUniform(localBuff, cutoff);

    snprintf(localBuff, sizeof(localBuff), "spotLights[%d].outer_cutoff", index);
    shader->SetUniform(localBuff, outer_cutoff);
}
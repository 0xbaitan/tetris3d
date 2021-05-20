#include "include/shadow.h"
#include <stdio.h>

Shadow::Shadow(unsigned int shadow_height, unsigned int shadow_width) {
    this->height = shadow_height;
    this->width = shadow_width;
    FBO = 0;
    depthMap = 0;
}


void Shadow::CreateDepthMap() {
    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width,
                 height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, black);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer error: %ud\n", Status);
    }
}

void Shadow::Write() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}

void Shadow::Read(GLenum tex_unit) {
    glActiveTexture(tex_unit);
    glBindTexture(GL_TEXTURE_2D, depthMap);
}

/** ---------------------------- Point Shadows ------------------------------*/

PointShadow::PointShadow(unsigned int shadow_height, unsigned int shadow_width) {
    this->height = shadow_height;
    this->width = shadow_width;
    FBO = 0;
    depth_cube_map = 0;
}
void PointShadow::CreateShadowMap() {

    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &depth_cube_map);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depth_cube_map);

    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                     width, height, 0, GL_DEPTH_COMPONENT,
                     GL_FLOAT, NULL);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    // glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, black);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_cube_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PointShadow::Write() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void PointShadow::Read(GLenum texUnit) {
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depth_cube_map);
}
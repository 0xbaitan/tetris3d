
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>

#include <GL/glew.h>

#ifndef SHADER_IMPLEMENTATION
#define SHADER_IMPLEMENTATION

#define SHADER_FILE_ABSENT NULL

class Shader {
public:
    Shader();

    void CreateFromFiles(const char *vertexFilePath, const char *fragFilePath, const char *geom_shader_path);
    void CreateFromFiles(const char *vertexFilePath, const char *fragFilePath);
    void UseProgram();

    void SetUniform(const std::string name, int value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }

    void SetUniform(const std::string name, unsigned int value) const {
        glUniform1ui(glGetUniformLocation(programID, name.c_str()), value);
    }
    void SetUniform(const std::string name, float value) const {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }
    void SetUniform(const std::string name, double value) const {
        glUniform1d(glGetUniformLocation(programID, name.c_str()), value);
    }
    void SetUniform(const std::string name, bool value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
    }
    void SetUniform(const std::string name, glm::mat4 matrix) const {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void SetUniform(const std::string name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
    }

    void SetUniform(const std::string name, glm::vec3 vector) const {
        glUniform3f(glGetUniformLocation(programID, name.c_str()), vector.x, vector.y, vector.z);
    }

     void SetUniform(const std::string name, size_t value) const {
        glUniform1ui(glGetUniformLocation(programID, name.c_str()), value);
    }
  

    unsigned int GetShaderID() const {
        return programID;
    }

    ~Shader();

private:
    GLuint programID;

    std::string ReadFile(const char *fileName);
    void CreateProgram(const char *vShaderCode, const char *fShaderCode, const char *gShaderCode);
    void CreateProgram(const char *vShaderCode, const char *fShaderCode);
    void CreateShader(GLuint programID, GLuint shaderType, const char *shaderCode);
    void DeleteShaders();
};

#endif //SHADER_IMPLEMENTATION
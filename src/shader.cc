#include "include/shader.h"

Shader::Shader() {

    programID = 0;
}

void Shader::CreateFromFiles(const char *vertexFilePath, const char *fragFilePath, const char *geom_shader_path) {

    std::string vShaderString = ReadFile(vertexFilePath);
    std::string fShaderString = ReadFile(fragFilePath);
    std::string gShaderString = ReadFile(geom_shader_path);
    const char *vShaderCode = vShaderString.c_str();
    const char *fShaderCode = fShaderString.c_str();
    const char *gShaderCode = gShaderString.c_str();
    CreateProgram(vShaderCode, fShaderCode, gShaderCode);
}

void Shader::CreateFromFiles(const char *vertexFilePath, const char *fragFilePath) {

    std::string vShaderString = ReadFile(vertexFilePath);
    std::string fShaderString = ReadFile(fragFilePath);

    const char *vShaderCode = vShaderString.c_str();
    const char *fShaderCode = fShaderString.c_str();

    CreateProgram(vShaderCode, fShaderCode);
}
void Shader::CreateProgram(const char *vShaderCode, const char *fShaderCode, const char *gShaderCode) {
    programID = glCreateProgram();

    if (!programID) {
        printf("Error creating shader program!\n");
        return;
    }
    CreateShader(programID, GL_VERTEX_SHADER, vShaderCode);
    CreateShader(programID, GL_FRAGMENT_SHADER, fShaderCode);
    CreateShader(programID, GL_GEOMETRY_SHADER, gShaderCode);
    glLinkProgram(programID);

    int success = 0;
    GLchar infoLog[1024] = {0};
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(programID, 1024, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s", infoLog);
    }
    glValidateProgram(programID);
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, sizeof(infoLog), NULL, infoLog);
        printf("Error validating program: '%s'\n", infoLog);
        return;
    }
}

void Shader::CreateProgram(const char *vShaderCode, const char *fShaderCode) {
    programID = glCreateProgram();

    if (!programID) {
        printf("Error creating shader program!\n");
        return;
    }
    CreateShader(programID, GL_VERTEX_SHADER, vShaderCode);
    CreateShader(programID, GL_FRAGMENT_SHADER, fShaderCode);
    // CreateShader(programID, GL_GEOMETRY_SHADER, gShaderCode);
    glLinkProgram(programID);

    int success = 0;
    GLchar infoLog[1024] = {0};
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(programID, 1024, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s", infoLog);
    }
    glValidateProgram(programID);
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, sizeof(infoLog), NULL, infoLog);
        printf("Error validating program: '%s'\n", infoLog);
        return;
    }
}

void Shader::UseProgram() {

    glUseProgram(programID);
}

void Shader::CreateShader(GLuint programID, GLuint shaderType, const char *shaderCode) {
    GLuint shaderID = glCreateShader(shaderType);

    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shaderID, 1, theCode, codeLength);
    glCompileShader(shaderID);

    int success = 0;
    GLchar infoLog[1024] = {0};
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
    }
    glAttachShader(programID, shaderID);
}

std::string Shader::ReadFile(const char *fileName) {
    std::string content;
    std::ifstream stream(fileName, std::ios::in);

    if (!stream.is_open()) {
        printf("%s file couldn't be opened\n", fileName);
        return "";
    }

    std::string line = "";
    while (!stream.eof()) {

        std::getline(stream, line);
        content.append(line + "\n");
    }
    stream.close();
    return content;
}

void Shader::DeleteShaders() {
}

Shader::~Shader() {

    if (programID != 0) {
        glDeleteProgram(programID);
        programID = 0;
    }
}
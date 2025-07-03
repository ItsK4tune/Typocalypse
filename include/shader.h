#pragma once

#include <string>
#include <glad/glad.h>

class Shader
{
public:
    Shader();
    Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");
    ~Shader();

    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setMat4(const std::string &name, const float *value) const;

private:
    unsigned int shaderID;
    std::string loadShaderSource(const std::string &filepath) const;
    unsigned int compileShader(unsigned int type, const char *source) const;
    unsigned int createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath) const;
    void checkCompileErrors(unsigned int shader, const std::string &type) const;
};
#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader()
    : shaderID(0)
{
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath)
    : shaderID(createShaderProgram(vertexPath, fragmentPath, geometryPath))
{
}

Shader::~Shader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
    }

    shaderID = 0;
}

std::string Shader::loadShaderSource(const std::string &filepath) const
{
    std::string fullPath = std::string("../../resources/shaders/") + filepath;

    std::ifstream file(fullPath);
    if (!file.is_open())
    {
        std::cerr << "Cannot read shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const char *source) const
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : type == GL_FRAGMENT_SHADER ? "FRAGMENT"
                                                                                                : "GEOMETRY");
    return shader;
}

unsigned int Shader::createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath) const
{
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);
    std::string geometryCode;

    if (!geometryPath.empty())
    {
        geometryCode = loadShaderSource(geometryPath);
    }

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
    unsigned int geometryShader = 0;

    if (!geometryPath.empty())
    {
        geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryCode.c_str());
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    if (geometryShader != 0)
    {
        glAttachShader(shaderProgram, geometryShader);
    }

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (geometryShader != 0)
    {
        glDeleteShader(geometryShader);
    }

    return shaderProgram;
}

void Shader::checkCompileErrors(unsigned int shader, const std::string &type) const
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::use() const
{
    glUseProgram(shaderID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float t) const
{
    glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, t);
}

void Shader::setMat4(const std::string &name, const float *value) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, value);
}

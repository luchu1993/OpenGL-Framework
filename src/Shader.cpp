#include "Shader.h"
#include <iostream>

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
    : m_vertexShaderFile(m_vertexShaderFile)
    , m_fragmentShaderFile(fragmentShaderFile)
{

}

bool Shader::init()
{
    int success;
    char errMsg[512];

    // Create and compile Vertext Shader 
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderCode = readShaderFromFile(m_vertexShaderFile);
    const char* vertexShaderCodes[] = { vertexShaderCode.c_str() };
    glShaderSource(vertexShader, 1, vertexShaderCodes, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, errMsg);
        std::cerr << "[ERROR]: Compile Vertex Shader failed at " 
            << __FILE__ << ": line " << __LINE__ << ". " << errMsg << std::endl;
        return false;
    }

    // Create and compile Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderCode = readShaderFromFile(m_fragmentShaderFile);
    const char* fragmentShaderCodes[] = { fragmentShaderCode.c_str() };
    glShaderSource(fragmentShader, 1, fragmentShaderCodes, nullptr);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, errMsg);
        std::cerr << "[ERROR]: Compile Fragment Shader failed at " 
            << __FILE__ << ": line " << __LINE__ << ". " << errMsg << std::endl;
        return false;
    }

    // Create Shader Program
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, errMsg);
        std::cerr << "[ERROR]: Create Shader Program failed at " 
            << __FILE__ << ": line " << __LINE__ << ". " << errMsg << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Shader::render()
{
    // Bind Shader Program
    glUseProgram(m_shaderProgram);
    // update uniform data
    
    return true;
}

void Shader::cleanup()
{
    
}

std::string Shader::readShaderFromFile(const char* fileName)
{

}
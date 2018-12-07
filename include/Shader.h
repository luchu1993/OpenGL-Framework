#ifndef __SHADER_H__
#define __SHADER_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

class Shader 
{
public:
    Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
    bool init();
    bool render();
    void cleanup();

protected:
    bool readShaderFromFile(const char* fileName, std::string& shaderCode);

private:
    unsigned int m_shaderProgram;
    const char* m_vertexShaderFile;
    const char* m_fragmentShaderFile;
};

#endif

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
    : m_vertexShaderFile(vertexShaderFile)
    , m_fragmentShaderFile(fragmentShaderFile)
{

}

bool Shader::init()
{
    int success;
    char errMsg[512];

    // Create and compile Vertext Shader 
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderCode;
	if (!readShaderFromFile(m_vertexShaderFile, vertexShaderCode))
	{
		std::cerr << "[ERROR]: Cannot open vertext shader file: "
			<< m_vertexShaderFile << " at " << __FILE__ << ": line " << __LINE__ <<std::endl;
		return false;
	}

    const char* vertexShaderCodes[] = { vertexShaderCode.c_str() };
    glShaderSource(vertexShader, 1, vertexShaderCodes, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, errMsg);
        std::cerr << "[ERROR]: Compile Vertex Shader failed at " 
            << __FILE__ << ": line " << __LINE__ << "\n" << errMsg << std::endl;
        return false;
    }

    // Create and compile Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderCode;
	if (!readShaderFromFile(m_fragmentShaderFile, fragmentShaderCode))
	{
		std::cerr << "[ERROR]: Cannot open fragment shader file: "
			<< m_fragmentShaderFile << " at " << __FILE__ << ": line " << __LINE__ << std::endl;
		return false;
	}

    const char* fragmentShaderCodes[] = { fragmentShaderCode.c_str() };
    glShaderSource(fragmentShader, 1, fragmentShaderCodes, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, errMsg);
        std::cerr << "[ERROR]: Compile Fragment Shader failed at " 
            << __FILE__ << ": line " << __LINE__ << "\n" << errMsg << std::endl;
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
            << __FILE__ << ": line " << __LINE__ << "\n" << errMsg << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	// 
	glGenBuffers(1, &m_transformUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, TransformsUniformBlock::BindingPoint, m_transformUBO);

    return true;
}

bool Shader::readShaderFromFile(const char* fileName, std::string& shaderCode)
{
	std::ifstream shaderFile(fileName);
	if (!shaderFile.is_open())
		return false;

	std::stringstream vertShaderStream;
	vertShaderStream << shaderFile.rdbuf();
	shaderCode = vertShaderStream.str();

	return true;
}


bool Shader::render
(
	glm::mat4 const& world,
	glm::mat4 const& view,
	glm::mat4 const& projection
)
{
	TransformsUniformBlock block;
	block.world = world;
	block.view = view;
	block.projection = projection;
	block.worldInvTranspose = glm::transpose(glm::inverse(world));

	glBindBuffer(GL_UNIFORM_BUFFER, m_transformUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(TransformsUniformBlock), &block, GL_STATIC_DRAW);

	glUseProgram(m_shaderProgram);

	return true;
}

void Shader::cleanup()
{
	glDeleteBuffers(1, &m_transformUBO);
	glDeleteProgram(m_shaderProgram);
}

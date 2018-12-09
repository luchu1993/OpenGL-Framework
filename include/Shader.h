#ifndef __SHADER_H__
#define __SHADER_H__

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>

class Shader 
{
	struct TransformsUniformBlock
	{
		glm::mat4 world;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 worldInvTranspose;
		static const unsigned int BindingPoint = 0;
	};
public:
    Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
    bool init();
    bool render
	(
		glm::mat4 const& world, 
		glm::mat4 const& view, 
		glm::mat4 const& projection
	);
    void cleanup();
	unsigned int getProgram() const { return m_shaderProgram; }

protected:
    bool readShaderFromFile(const char* fileName, std::string& shaderCode);

private:
    unsigned int m_shaderProgram;
    const char* m_vertexShaderFile;
    const char* m_fragmentShaderFile;
	unsigned int m_transformUBO;
};

#endif

#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 vTexCoord;

out vec3 posW;
out vec3 normalW;
out vec2 texCoord;

layout (std140, binding = 0)
uniform Transforms
{
	mat4 world;
	mat4 view;
	mat4 projection;
	mat4 worldInvTranspose;
};

void main()
{
	gl_Position = projection * view * world * vec4(position, 1.0f);
	posW = (world * vec4(position, 1.0f)).xyz;
	normalW = mat3(worldInvTranspose) * normal;
	texCoord = vTexCoord;
}

#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 posW;
out vec3 normalW;

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
}

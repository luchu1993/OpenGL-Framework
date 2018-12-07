#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 posW;
out vec3 normalW;

uniform Transforms
{
    uniform mat4 world;
    uniform mat4 view;
    uniform mat4 projection;
    uniform mat4 worldInvTranspose;  // 法向量变换
};

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    posW = world * vec4(position, 1.0f).xyz;
    normalW = (mat3)worldInvTranspose * normal;
}

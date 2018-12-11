#version 450 core

in vec3 posW;
in vec3 normalW;

out vec4 fragColor;

uniform vec3 eyePosW;

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shineness;
};

struct PointLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
    vec3 attenuation;
    float range;
};

struct DirectionalLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 direction;
};

layout (std140, binding = 1)
uniform ub_DirectionalLight
{
    DirectionalLight dirLight;
};

layout (std140, binding = 2)
uniform ub_PointLight
{
    PointLight pointLight;
};

layout (std140, binding = 3)
uniform ub_Material
{
    Material mat;
};


void main()
{
    vec3 N = normalize(normalW);
    vec3 L = normalize(dirLight.direction);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(eyePosW - posW);

    // directional light
    vec4 ambient = dirLight.ambient * mat.ambient;
    vec4 diffuse = max(dot(N, L), 0.0f) * dirLight.diffuse * mat.diffuse;
    vec4 specular = pow(max(dot(R, V), 0.0f), mat.shineness) * dirLight.specular * mat.specular;

    // point light
    ambient += pointLight.ambient * mat.ambient;
    
    float D = length(eyePosW - posW);
    if (D <= pointLight.range)
    {
        L = normalize(pointLight.position - posW);
        R = reflect(-L, N);
        float att = pointLight.attenuation.x + pointLight.attenuation.y * D + pointLight.attenuation.z * D * D;
        diffuse += (max(dot(N, L), 0.0f) * pointLight.ambient * mat.ambient) / att;
        specular += pow(max(dot(R, V) ,0.0f), mat.shineness) * pointLight.specular * mat.specular / att;
    }

    fragColor = ambient + diffuse + specular;
}
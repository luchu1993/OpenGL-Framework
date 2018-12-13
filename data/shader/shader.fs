#version 450 core

in vec3 posW;
in vec3 normalW;
in vec2 texCoord;

out vec4 fragColor;

uniform vec3 eyePosW;
uniform sampler2D tex;

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

void main()
{
    vec3 N = normalize(normalW);
    vec3 L = normalize(dirLight.direction);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(eyePosW - posW);

    // directional light
    vec4 ambient = dirLight.ambient;
    vec4 diffuse = max(dot(N, L), 0.0f) * dirLight.diffuse;
    vec4 specular = pow(max(dot(R, V), 0.0f), 64.0f) * dirLight.specular;

    // point light
    ambient += pointLight.ambient ;
    diffuse += vec4(0.0f);
    specular += vec4(0.0f);

    float D = length(pointLight.position - posW);
    if (D <= pointLight.range)
    {
        L = normalize(pointLight.position - posW);
        R = reflect(-L, N);
        float att = pointLight.attenuation.x + pointLight.attenuation.y * D + pointLight.attenuation.z * D * D;
        diffuse += max(dot(N, L), 0.0f) * pointLight.diffuse / att;
        specular += pow(max(dot(R, V) ,0.0f), 64.0f) * pointLight.specular / att;
    }

    vec4 texel = texture(tex, texCoord);
    fragColor = (ambient + diffuse) * texel + specular;
}
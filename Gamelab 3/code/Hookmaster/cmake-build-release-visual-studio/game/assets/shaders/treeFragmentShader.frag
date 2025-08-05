#version 460 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

uniform vec3 lightPos = vec3 (0, 5, 0);
uniform vec4 color = vec4(0.945f, 0.768f, 0.058f, 1.0f);
uniform vec3 viewPos;
uniform float specularStrength = 0.5f;
uniform float ambient = 1.0f;
out vec4 fragColor;

uniform sampler2D texture0;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(fragPos - lightPos);
    float attenuation = max(dot(norm, lightDir), 0.0f);

    vec3 viewDir = normalize(fragPos - viewPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    float specular = specularStrength * spec;
    vec3 result = (ambient + attenuation + specular) * vec3(color) / 2;
    fragColor = vec4(result, 1.0f);
}
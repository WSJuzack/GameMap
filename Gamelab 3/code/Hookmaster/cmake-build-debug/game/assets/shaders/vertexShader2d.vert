#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 mvp;
uniform mat4 modelToWorldNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec2 texCoord;
out vec3 fragPos;
out vec3 lightPos;

void main()
{
    fragPos = vec3(view * model * projection * vec4(aPosition, 1.0));
    normal = vec3(modelToWorldNormal * vec4(aNormal, 0.0f));
    gl_Position = mvp * vec4(aPosition, 1.0f);
    texCoord = aTexCoord;
}
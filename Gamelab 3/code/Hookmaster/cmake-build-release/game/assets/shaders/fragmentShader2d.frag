#version 460 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

uniform vec4 color;
uniform sampler2D texture0;

out vec4 fragColor;

void main() {
    fragColor = texture(texture0, texCoord) * color;
}


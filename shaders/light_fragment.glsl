#version 330 core

in vec3 fragmentVertexNormal;
in vec2 fragmentTexCoord;

out vec4 color;

uniform vec4 lightColor;

void main()
{
    color = lightColor;
}
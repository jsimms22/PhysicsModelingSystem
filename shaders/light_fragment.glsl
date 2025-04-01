#version 330 core

out vec4 color;

in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec4 lightColor;

void main()
{
    color = lightColor;
}

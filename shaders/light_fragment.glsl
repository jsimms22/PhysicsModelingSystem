#version 330 core

in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform vec4 lightColor;

void main()
{
    color = lightColor;
}

#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 3) in vec4 vertexColor;

uniform mat4 model;
uniform mat4 cameraMatrix;

out vec3 fragNormal;
out vec2 fragTexCoord;

void main()
{
    gl_Position = cameraMatrix * model * vec4(vertexPosition, 1.0);
    fragNormal = vertexNormal;
    fragTexCoord = vertexTexCoord;
}


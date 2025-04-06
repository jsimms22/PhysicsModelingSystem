#version 410 core

layout (location = 0) in dvec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 3) in vec4 vertexColor;

uniform dmat4 model;
uniform dmat4 cameraMatrix;

void main()
{
    gl_Position = vec4(cameraMatrix * model * dvec4(vertexPosition,1.0));
}


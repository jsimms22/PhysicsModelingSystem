#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragNormal; 
out vec3 currentPos; 
out vec2 fragTexCoord;

void main()
{
    // Output to fragment shader
    fragNormal = vertexNormal;
    fragTexCoord = vertexTexCoord;
    currentPos = vec3(model * vec4(vertexPos, 1.0f));

    gl_Position = projection * view * vec4(currentPos, 1.0);
}
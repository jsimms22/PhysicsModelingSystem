#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 4) in vec4 instanceMatrix;

uniform mat4 cameraMatrix;

out vec3 fragPosition;
out vec3 fragNormal;  
out vec2 fragTexCoord;

void main()
{
    // Output to fragment shader
    fragNormal = vertexNormal;
    fragTexCoord = vertexTexCoord;
    fragPosition = vec3(instanceMatrix * vec4(vertexPosition, 1.0));

    gl_Position = cameraMatrix * vec4(currentPos, 1.0);
}
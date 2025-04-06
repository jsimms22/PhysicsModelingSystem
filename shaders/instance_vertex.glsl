#version 410 core

layout (location = 0) in dvec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 4) in dvec4 instanceMatrix;

uniform dmat4 cameraMatrix;

out vec3 fragPosition;
out vec3 fragNormal;  
out vec2 fragTexCoord;

void main()
{
    // Output to fragment shader
    fragNormal = vertexNormal;
    fragTexCoord = vertexTexCoord;
    fragPosition = vec3(instanceMatrix * dvec4(vertexPosition, 1.0));

    gl_Position = vec4(cameraMatrix * dvec4(currentPos, 1.0));
}
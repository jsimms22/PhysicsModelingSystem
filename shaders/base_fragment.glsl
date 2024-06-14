#version 330 core

in vec3 fragmentVertexNormal;
in vec3 currentPos;
in vec2 fragmentTexCoord;

out vec4 color;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

float near = 0.1;
float far = 200.0;

float LinearizeDepth(float depth);

void main()
{
    vec3 normal = normalize(fragmentVertexNormal);
    vec3 lightDir = normalize(lightPos - currentPos);

    // different types of light
    float ambient = 0.2f;

    float diffuse = max(dot(normal,lightDir), 0.0f);

    // float specularLight = 0.50f;
    // vec3 viewDir = normalize(camPos - currentPos);
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float specularAmt = pow(max(dot(viewDir, reflectDir), 0.0f), 5);
    // float specular = specularLight * specularAmt;

    // ratio of distance and depth
    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    color = vec4(1.0, 1.0, 1.0, depth) * lightColor * (diffuse + ambient*2); // could add specular light
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

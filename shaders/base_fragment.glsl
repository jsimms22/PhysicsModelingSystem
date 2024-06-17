#version 330 core

out vec4 color;

in vec3 currentPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth);
vec4 pointLight();

void main()
{
    // Calc visibility based on distance in the relative z-axis
    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    // Final lighting calc
    vec4 point = pointLight();
    color = vec4(0.1f, 0.1f, 0.1f, depth) + point;
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

vec4 pointLight()
{
    vec3 lightVec = lightPos - currentPos;

    // LIGHT INTENSITY CALC
    float dist = length(lightVec);
    // Quadratic terms
    float a = 0.00003f; 
    float b = 0.001f;
    float intensity = (1.0f / (a*(dist*dist) + b * dist + 1.0f));

    // AMBIENT LIGHT CALC
    float ambient = 0.1f;

    // DIFFUSE LIGHT CALC
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(normal,lightDir), 0.0f);

    // float specularLight = 0.50f;
    // vec3 viewDir = normalize(camPos - currentPos);
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float specularAmt = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
    // float specular = specularLight * specularAmt;
    
    return ((diffuse * intensity + ambient) * lightColor) ; // + (specular * intensity)
}

#version 410 core

out vec4 color;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec4 lightColor;
uniform dvec3 lightPosition;
uniform dvec3 cameraPosition;

double near = 0.1;
double far = 250.0;

double LinearizeDepth(double depth);

vec4 pointLight();

void main()
{
    // Calc visibility based on distance in the relative z-axis
    double depth = LinearizeDepth(double(gl_FragCoord.z)) / far;
    // First iteration of lighting
    vec4 point = pointLight();
    color = vec4(0.0f, 0.0f, 0.0f, float(depth)) + point;
}

double LinearizeDepth(double depth)
{
    double z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

vec4 pointLight()
{
    // AMBIENT LIGHT CALC
    float ambient = 0.3f;

    // DIFFUSE LIGHT CALC
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(vec3(lightPosition) - fragPosition);
    float diffuse = max(dot(normal, lightDir), 0.0f);

    // LIGHT INTENSITY CALC
    float dist = length(lightDir);
    // Quadratic terms
    float a = 0.00003f; 
    float b = 0.0001f;
    float intensity = .5f * (1.0f / (a*(dist*dist) + b * dist + 1.0f));

    // SPECULAR LIGHT
    float specularLight = 0.1f;
    vec3 viewDir = normalize(cameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularAmt = pow(max(dot(viewDir, reflectDir), 0.0f), .5);
    float specular = specularLight * specularAmt;
    
    vec4 color = (((diffuse + specular) * intensity ) * lightColor) + vec4(0.1f,0.1f,0.1f,ambient);
    return color;
}
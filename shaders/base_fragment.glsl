#version 410 core

out vec4 color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight
{
    dmat4 model;
    dvec3 position;
    vec4 color;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec4 modelColor;
uniform vec4 lightColor;
uniform dvec3 lightPosition;
uniform dvec3 cameraPosition;

#define MAX_POINT_LIGHTS 10
uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform Material material;

double near = 0.1;
double far = 250.0;

double LinearizeDepth(double depth);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Calc visibility based on distance in the relative z-axis
    double depth = LinearizeDepth(double(gl_FragCoord.z)) / far;

    // Second iteration of lighting properties
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(vec3(cameraPosition) - fragPosition);

    vec3 result = vec3(0.0);
    // phase 0: Ambient Universal lighting
    result += vec3(.1);

    // phase 1: Point lights
    for (int i = 0; i < numPointLights; ++i)
    {
        result += CalcPointLight(pointLights[i], norm, fragPosition, viewDir);
    }

    // phase 2: Model color and depth then combine
    color = vec4(0.0f, 0.0f, 0.0f, float(depth)) + vec4(result,0.1) + modelColor;
}

double LinearizeDepth(double depth)
{
    double z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightWorldPos = vec3(light.model * dvec4(light.position, 1.0));
    vec3 lightDir = normalize(lightWorldPos - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    // attenuation
    float distance = length(lightWorldPos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;//  * vec3(texture(material.diffuse, fragTexCoord));
    vec3 specular = light.specular * spec;//  * vec3(texture(material.specular, fragTexCoord));

    return (ambient + diffuse + specular) * vec3(light.color) * attenuation;
}
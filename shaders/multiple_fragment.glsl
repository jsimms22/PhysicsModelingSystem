#version 410 core
out vec4 color;

struct DirLight 
{
    vec3 direction;
    vec4 color;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    dvec3 position;
    vec4 color;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform dvec3 cameraPosition;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Second iteration of lighting properties
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(vec3(cameraPosition) - fragPosition);

    vec4 result;
    // phase 1: Directional lighting
    result = CalcDirLight(dirLight, norm, viewDir);

    // phase 2: Point lights
    for (int i = 0; (i < NR_POINT_LIGHTS); ++i) {
        result += CalcPointLight(pointLights[i], norm, fragPosition, viewDir);
    }

    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, vfragPosition, viewDir);

    // Calc visibility based on distance in the relative z-axis
    result.w = 1.0f;
    color = result; 
}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 1.0f);

    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    return vec4((ambient + diffuse + specular),1.0f) * light.color;
}  

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 1.0f);

    // attenuation
    float distance    = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));   
                 
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return vec4((ambient + diffuse + specular),1.0f) * light.color;
}
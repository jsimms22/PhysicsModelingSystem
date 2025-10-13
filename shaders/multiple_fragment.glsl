#version 410 core
out vec4 color;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

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

struct SpotLight 
{
    dvec3 position;
    vec3 direction;
    vec4 color;
    float cutOff;
    float outerCutOff;
  
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

#define MAX_POINT_LIGHTS 10
uniform int numPointLights;
uniform dvec3 cameraPosition;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Second iteration of lighting properties
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(vec3(cameraPosition) - fragPosition);
    vec4 result = vec4(0.0);

    // phase 1: Directional lighting
    //result = CalcDirLight(dirLight, norm, viewDir);

    // phase 2: Point lights
    for (int i = 0; i < numPointLights; ++i) {
        result += CalcPointLight(pointLights[i], norm, fragPosition, viewDir);
    }

    // phase 3: Spot light
    result += CalcSpotLight(spotLight, norm, fragPosition, viewDir);

    // Calc visibility based on distance in the relative z-axis
    result.w = 1.0f;
    color = result; 
}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    // combine results
    vec3 ambient  = vec3(0.0); //light.ambient;
    vec3 diffuse  = light.diffuse  * diff;//  * vec3(texture(material.diffuse, fragTexCoord));
    vec3 specular = light.specular * spec;//  * vec3(texture(material.specular, fragTexCoord));

    //ambient  *= attenuation;
    //diffuse  *= attenuation;
    //specular *= attenuation;

    return vec4((ambient + diffuse + specular),1.0f) * light.color;
}  

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    // attenuation
    float distance = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));   
                 
    // combine results
    vec3 ambient  = vec3(0.0); //light.ambient;
    vec3 diffuse  = light.diffuse  * diff;//  * vec3(texture(material.diffuse, fragTexCoord));
    vec3 specular = light.specular * spec;//  * vec3(texture(material.specular, fragTexCoord));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return vec4((ambient + diffuse + specular),1.0f) * light.color;
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    // attenuation
    float distance = length(vec3(light.position) - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    // combine results
    vec3 ambient  = vec3(0.0); //light.ambient;
    vec3 diffuse  = light.diffuse  * diff;// * vec3(texture(material.diffuse, fragTexCoord));
    vec3 specular = light.specular * spec;// * vec3(texture(material.specular, fragTexCoord));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return vec4((ambient + diffuse + specular),1.0f) * light.color;
}
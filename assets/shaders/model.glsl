#version 330 core

#ifdef VERTEX

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;
layout (location = 3) in mat4 vInstanceMatrix;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 uViewProjectionMatrix;

void main()
{
    Normal = vNormal;
    TexCoords = vTexCoords;
    vec4 pos = vInstanceMatrix * vec4(vPos, 1.0);
    FragPos = vec3(pos);
    gl_Position = uViewProjectionMatrix * pos;
}

#endif

#ifdef FRAGMENT

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float minSpecular;
    float shininess;
    vec3 diffuseColor;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int pointLightsBound;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 GetSpecular();
vec3 GetMaterialDiffuseColor();

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < pointLightsBound && i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);   
        
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 ambient = light.ambient * GetMaterialDiffuseColor();
    vec3 diffuse = light.diffuse * diff * GetMaterialDiffuseColor();
    vec3 specular = light.specular * spec * GetSpecular();
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    float dist = length(light.position - fragPos);
    float denominator = max(light.constant + light.linear * dist + light.quadratic * (dist * dist), 0.001);
    float attenuation = 1.0 / denominator;    
    
    vec3 ambient = light.ambient * GetMaterialDiffuseColor();
    vec3 diffuse = light.diffuse * diff * GetMaterialDiffuseColor();
    vec3 specular = light.specular * spec * GetSpecular();
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return light.color * (ambient + diffuse + specular);
}

vec3 GetSpecular()
{
    return vec3(max(texture(material.specular, TexCoords), material.minSpecular));
}

vec3 GetMaterialDiffuseColor()
{
    return vec3(texture(material.diffuse, TexCoords)) * material.diffuseColor;
}

#endif
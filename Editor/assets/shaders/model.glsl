#version 330 core

#ifdef VERTEX

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 uViewProjectionMatrix;

void main()
{
    Normal = vNormal;
    TexCoords = vTexCoords;    
    FragPos = vec3(model * vec4(vPos, 1.0));
    gl_Position = uViewProjectionMatrix * model * vec4(vPos, 1.0);
}

#endif

#ifdef FRAGMENT

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform sampler2D texture_diffuse1;

void main()
{    
    vec3 lightColor = vec3(1.0);

    vec3 ambient = lightColor * material.ambient;
  	
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);  
        
    vec3 result = (ambient + diffuse + specular) * vec3(texture(texture_diffuse1, TexCoords));
    FragColor = vec4(result, 1.0);
}

#endif
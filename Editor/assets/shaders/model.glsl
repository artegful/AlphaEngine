#version 330 core

#ifdef VERTEX

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 uViewProjectionMatrix;

void main()
{
    TexCoords = vTexCoords;    
    gl_Position = uViewProjectionMatrix * model * vec4(vPos, 1.0);
}

#endif

#ifdef FRAGMENT

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}

#endif
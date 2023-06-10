#version 330 core

#ifdef VERTEX

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uViewProjectionMatrix;

void main()
{
    TexCoords = aPos;
    vec4 pos = uViewProjectionMatrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  

#endif

#ifdef FRAGMENT

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}

#endif
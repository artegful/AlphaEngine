#version 330 core

#ifdef VERTEX

layout (location = 0) in vec3 vPosition;

uniform mat4 uModelMatrix;
uniform mat4 uViewProjectionMatrix;

void main()
{
	gl_Position = uViewProjectionMatrix * uModelMatrix * vec4(vPosition, 1.0f);
}

#endif

#ifdef FRAGMENT

uniform vec4 uColor;

out vec4 color;

void main()
{
	color = uColor;
}

#endif
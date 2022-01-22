#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUv;
layout (location = 3) in int aTextureId;

uniform mat4 projection;
uniform mat4 view;

out vec4 fColor;
out vec2 fUv;
flat out int fTextureId;

void main()
{
	gl_Position = projection * view * vec4(aPosition, 1.0f);

	fColor = aColor;
	fUv = aUv;
	fTextureId = aTextureId;
}
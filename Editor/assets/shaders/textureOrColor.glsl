#version 330 core

#ifdef VERTEX

uniform mat4 uViewProjectionMatrix;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vUv;
layout (location = 3) in float vTextureIndex;
layout (location = 4) in float vTiling;

out vec2 fUv;
out vec4 fColor;
flat out float fTextureIndex;
flat out float fTiling;

void main()
{
	gl_Position = uViewProjectionMatrix * vec4(vPosition, 1.0f);
	fColor = vColor;
	fUv = vUv;
	fTextureIndex = vTextureIndex;
	fTiling = vTiling;
}

#endif

#ifdef FRAGMENT

uniform sampler2D uTextures[32];

in vec4 fColor;
in vec2 fUv;
flat in float fTextureIndex;
flat in float fTiling;

out vec4 color;

void main()
{
	color = texture(uTextures[int(fTextureIndex)], fUv * fTiling) * fColor;
}

#endif
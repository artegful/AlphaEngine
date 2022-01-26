#type vert
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

#type frag
#version 330 core

in vec4 fColor;
in vec2 fUv;
flat in int fTextureId;

uniform sampler2D textures[8];

out vec4 color;

void main()
{
	if (fTextureId < 0)
	{
		color = fColor;
	}
	else
	{
		color = texture(textures[fTextureId], fUv);
	}
}
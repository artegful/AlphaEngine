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
#version 460 core
in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D image;

void main()
{
	FragColor = texture(image, v_TexCoord);
}
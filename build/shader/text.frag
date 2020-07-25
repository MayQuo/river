#version 460 core
out vec4 FragColor;

in vec2 v_texCoord;

uniform sampler2D u_texture;
uniform vec3 u_color;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, v_texCoord).r);
	FragColor = vec4(u_color, 1.0) * sampled;
}
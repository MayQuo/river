#version 460 core
layout (location = 0) in vec4 aVertex;

uniform mat4 u_projection;

out vec2 v_texCoord;

void main()
{
	gl_Position = u_projection * vec4(aVertex.xy, 0.0, 1.0);
	v_texCoord = aVertex.zw;
}
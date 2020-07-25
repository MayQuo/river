#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 v_TexCoord;

uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * vec4(aPos.xy, 0.0, 1.0);
	v_TexCoord = aTexCoord;
}

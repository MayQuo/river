#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 v_TexCoord;

uniform mat4 projection;
uniform mat4 model;

void main() {
	gl_Position = projection * model * vec4(aPos.xy, 0.0, 1.0);
	v_TexCoord = aTexCoord;
}
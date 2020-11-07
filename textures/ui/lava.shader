shader_type canvas_item;

uniform sampler2D noise;

void fragment() {
	COLOR = texture(noise, vec2(UV.x+TIME*2.0, UV.y-1.0)) + vec4(0.7, 0.2, 0.0, UV.y) * vec4(0.8+abs(sin(TIME*0.5)), 0.1+abs(sin(TIME*1.0)), 0.0, 1.0);
}
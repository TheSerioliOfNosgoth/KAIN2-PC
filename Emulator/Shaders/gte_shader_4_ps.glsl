#version 330


mat4 dither = mat4(
	-4.0,  +0.0,  -3.0,  +1.0,
	+2.0,  -2.0,  +3.0,  -1.0,
	-3.0,  +1.0,  -4.0,  +0.0,
	+3.0,  -1.0,  +2.0,  -2.0) / 255.0;
			
vec3 DITHER(const ivec2 dc) {
for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	if(i == dc.x && j == dc.y) {
		return vec3(dither[i][j] * v_texcoord.w); }
		}
	}
}
	
uniform sampler2D s_lut;
	
vec2 VRAM(vec2 uv) { return texture(s_texture, uv).rg; }
	
void main() {
	ivec2 dc = ivec2(fract(gl_FragCoord.xy / 4.0) * 4.0);
	fragColor.xyz += DITHER(dc);
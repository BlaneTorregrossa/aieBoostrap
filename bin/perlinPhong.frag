#version 410
in vec2 vTexCoord;
out vec4 fragColor;
uniform sampler2D perlinTexture;
void main() {
fragColor = texture(perlinTexture,vTexCoord).rrrr;
fragColor.a = 1;
}
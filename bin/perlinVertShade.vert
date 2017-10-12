#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec2 texCoord;
uniform mat4 projectionView;
out vec2 vTexCoord;
uniform sampler2D perlinTexture;
void main() {
vec4 pos = position;
pos.y += texture(perlinTexture, texCoord).r * 15;

vTexCoord = texCoord;
gl_Position = projectionView * pos;
}
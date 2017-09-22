#version 410
layout(location=0) in vec4 position; 
layout(location=1) in vec4 colour;
layout(location=2) in vec4 normal;
layout(location=3) in vec4 tangent;
layout(location=4) in vec4 bitangent;
layout(location=5) in vec2 texcoord;

out vec4 vPosition;
out vec4 vColour;
out vec4 vNormal;
out vec4 vTangent;
out vec4 vBitangent;
out vec2 vTexcoord;

uniform mat4 projectionView;
void main() 
{ 
vPosition = position;
vNormal = normal;
vColour = colour; 
vTangent = tangent;
vBitangent = bitangent;
vTexcoord = texcoord;
gl_Position = projectionView * position; 
}
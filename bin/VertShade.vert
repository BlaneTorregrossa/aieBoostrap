#version 410
layout(location=0) in vec4 position; 
layout(location=1) in vec4 normal;


out vec4 vNormal;
out vec4 vPosition;

uniform mat4 projectionViewWorldMatrix;

void main() { 
vNormal = normal;
vPosition = position;
gl_Position = projectionViewWorldMatrix * position;
}
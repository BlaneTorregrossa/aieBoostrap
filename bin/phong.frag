#version 410

in vec4 vNormal;
in vec4 vPosition;

out vec4 fragColor;

void main() 
{ 
float diffuse = max(0, dot(normalize(vNormal.xyz), vec3(0,1,0)));
fragColor = vec4(diffuse,diffuse,diffuse,1); 
}
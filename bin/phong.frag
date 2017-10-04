#version 410
in vec2 vTexCoord;
in vec4 vBitangent;
in vec4 vTangent;
in vec4 vColour;
in vec4 vNormal;
in vec4 vPosition;

out vec4 fragColour;

void main() 
{ 
	float diffuse = max(0, dot(normalize(vNormal.xyz), vec3(0,1,0)));
	fragColour = vec4(diffuse,diffuse,diffuse,1); 
}
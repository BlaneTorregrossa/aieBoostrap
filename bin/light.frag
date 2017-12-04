#version 410

// ambient KaIa
vec4 Ka = vec4(1,0,0,1);
vec4 Ia = vec4(0.25f,0.25f,0.25f,1);

// diffuse KdId
vec4 Kd = vec4(1,0,0,1);
vec4 Id = vec4(1,1,1,1);

// Specular KsIs
vec4 Ks = vec4(1,0,0,1);
vec4 Is = vec4(1,1,1,1);

uniform float specularPower = 32.0f;

vec3 L; // light direction
vec3 R; // Reflected ray
vec3 V; // viewing vector (camera)
vec3 N; // vNormal after being Normalized 

in vec2 vTexCoord;
in vec4 vBitangent;
in vec4 vTangent;
in vec4 vColour;
in vec4 vNormal;
in vec4 vPosition;

out vec4 fragColour;

void main()
{

// ------------------------------------------------------------------------------------------------------
// ambient
// ------------------------------------------------------------------------------------------------------

vec4 ambient = Ka * Ia;	// ambient light

// ------------------------------------------------------------------------------------------------------
// diffuse
// ------------------------------------------------------------------------------------------------------

L = normalize();
N = normalize(vNormal.xyz);

// dot product between the surface normal and light direction
float LambertDiffuseTerm = max(0.0f, dot(N,-L));
vec4 diffuse = Kd * Id * LambertDiffuseTerm;	// diffuses light

// ------------------------------------------------------------------------------------------------------
// specular
// ------------------------------------------------------------------------------------------------------


R = reflect(L,N);
V = normalize(camera.xyz - vPosition.xyz); 

float specTerm = pow( max(0.0f, dot(R,V)), specularPower);
vec4 specular = Ks * Is * specTerm;	// specular light

// ------------------------------------------------------------------------------------------------------
// phong lighting
// ------------------------------------------------------------------------------------------------------

fragColour = vec4(ambient + diffuse + specular, 1);

}








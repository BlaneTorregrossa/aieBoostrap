#include "Shader.h"

#include <Gizmos.h>

Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::startup()
{
	return false;
}

void Shader::shutdown()
{
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

void Shader::update(float)
{
}

void Shader::draw()
{
}

void Shader::bind()
{
	glLinkProgram(m_program);
}

void Shader::unbind()
{
	glLinkProgram(0);
}

void Shader::defaultload()
{
	// From the guide from last wednesday/thursday

	vsSource = "#version 410\n \
				in vec4 Position; \
				in vec4 Colour; \
				out vec4 vColour; \
				out vec4 vPosition; \
				uniform mat4 ProjectionView; \
				void main() { \
				vColour = Colour; vPosition = Position; \
				gl_Position = ProjectionView * Position; }";

	fsSource = "#version 410\n \
				in vec4 vColour; \
				in vec4 vPosition; \
				out vec4 FragColor; \
				uniform vec3 LightDir; \
				uniform vec3 LighColour; \
				uniform vec3 CameraPos; \
				uniform float SpecPos; \
				void main() { float d = max(0, dot ( normalize(vNormal.xyz), LightDir ) );\
				vec3 E = normalize ( CameraPos - vPosition.xyz ); \
				vec3 R = reflect ( -LightDir, vNormal.xyz ); \
				float s = max (0, dot( E, R ) ) ; \
				s = pow( s, SpecPow ); \
				FragColor = vec4( LightColour * d + LightColour * s, 1); }";

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	attach();
}

void Shader::load(const char * filename, unsigned int type)
{
}

void Shader::attach()
{
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
}

unsigned int Shader::getUniform(const char *)
{
	return 0;
}

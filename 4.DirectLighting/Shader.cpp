#include "Shader.h"


#include <gl_core_4_4.h>
Shader::Shader() : file(0)
{
	file = new Filer();
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
	const char* vsSource = "#version 410\n \
	layout(location=0) in vec4 position; \
	layout(location=1) in vec4 colour; \
	out vec4 vColour; \
	uniform mat4 projectionView; \
	void main() { vColour = colour; gl_Position =\
	projectionView * position; }";
	const char* fsSource = "#version 410\n \
	in vec4 vColour; \
	out vec4 fragColour;\
	void main() { fragColour = vColour; }";
	//file->writeIt("Vertex.vert", vsSource);
	//file->writeIt("Fragment.frag", fsSource);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//specify where the source is located and bind to the specific shader handle
	glShaderSource(vertexShader, 1, (const char **)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_program = glCreateProgram();
	this->attach();
	glLinkProgram(m_program);
	int success = GL_FALSE;
	// check that it compiled and linked correctly
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
}

void Shader::load(const char * filename, unsigned int type)
{
	const char* contents = file->readIt(filename);
	switch (type)
	{
	case GL_VERTEX_SHADER:

		vertexShader = glCreateShader(type);
		glShaderSource(vertexShader, 1, (const char **)&contents, 0);
		glCompileShader(vertexShader);
		break;

	case GL_FRAGMENT_SHADER:

		fragmentShader = glCreateShader(type);
		glShaderSource(fragmentShader, 1, (const char **)&contents, 0);
		glCompileShader(fragmentShader);
		break;
	default:
		break;
	}
}

void Shader::attach()
{
	m_program = glCreateProgram();

	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	
	glLinkProgram(m_program);
	
	int success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
}

unsigned int Shader::getUniform(const char * uniform)
{
	return glGetUniformLocation(m_program, uniform);
}

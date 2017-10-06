#include "Shader.h"


#include <gl_core_4_4.h>
Shader::Shader() : file(0)
{
	file = new Filer();
}


Shader::~Shader()
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

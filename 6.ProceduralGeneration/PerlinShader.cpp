#include "PerlinShader.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace glm;
using namespace std;

PerlinShader::PerlinShader() : file(0)
{
	file = new PerlinFiler();
}

PerlinShader::~PerlinShader()
{
}

void PerlinShader::load(const char * filename, unsigned int type)
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

void PerlinShader::attach()
{
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	//Checks if shader linked to program
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

void PerlinShader::genPerlinValue()
{
	int dims = 64;
	perlinData = new float[dims * dims];
	float scale = (1.0f / dims) * 3;
	for (int x = 0; x < 64; ++x)
	{
		for (int y = 0; y < 64; ++y)
		{
			perlinData[y * dims + x] = perlin(vec2(x, y) * scale) * 0.5f + 0.5f;
		}
	}
}

void PerlinShader::genPerlinTextures()
{
	int imageWidth, imageHeight, imageFormat;
	unsigned char* data = stbi_load("./textures/crate.png", &imageWidth, &imageHeight, &imageFormat, 0);

	glGenTextures(1, &m_texture);	// used to generate many texture handles at once
	glBindTexture(GL_TEXTURE_2D, m_texture);	// bind the textures to the correct slot

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 64, 64, 0, GL_RED, GL_FLOAT, perlinData);	// speciy the data for the texture. 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}


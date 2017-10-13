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

using namespace glm;
using namespace std;

PerlinShader::PerlinShader() : file(0)
{
	file = new PerlinFiler();
}

PerlinShader::~PerlinShader()
{
}

// Loads shaders from file when given a filename and shader type
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

// Attaches and then links shaders to the program
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

// For generating noise
void PerlinShader::genNoiseValue(float width, float height)
{
	perlinData = new float[width * height];
	float scale = 0;
	int octaves = 8;

	if ((1 / height) == (1 / width))
	{
		scale = 1 / width;
		scale *= 5;
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float amplitude = 1.f;
			float persistence = 0.3f;
			perlinData[y * 64 + x] = 0;
			for (int o = 0; o < octaves; o++)
			{
				float freq = powf(2, (float)o);
				//float perlinSample = glm::perlin(vec2(x, y) * scale * freq) * 0.5f + 0.5f;	// the sample
				float blaneNoise = noise(vec2(x, y) * scale * freq) * 0.5f + 0.5f;	// to do what perlin does (FIX!!!)
				perlinData[y * 64 + x] += blaneNoise * amplitude;
				amplitude *= persistence;
			}
		}

	}
}

//	trash (Due for rework)
float PerlinShader::noise(vec2 pos)
{
	float tmpValue = 0;

	return tmpValue;
}

//	Genertate perlin textures 
void PerlinShader::genPerlinTextures()
{
	glGenTextures(1, &m_texture);	// used to generate many texture handles at once
	glBindTexture(GL_TEXTURE_2D, m_texture);	// bind the textures to the correct slot

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 64, 64, 0, GL_RED, GL_FLOAT, perlinData);	// speciy the data for the texture. 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


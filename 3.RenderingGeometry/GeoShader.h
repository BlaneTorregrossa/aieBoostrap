#pragma once
#include <stdio.h>
#include <vector>
#include <glm\glm.hpp>
#include "GeoFiler.h"

class Shader
{
public:
	Shader();
	~Shader();

	void load(const char * filename, unsigned int type);
	void attach();

	Filer* file;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int m_program;
	const char* vsSource;
	const char* fsSource;

};


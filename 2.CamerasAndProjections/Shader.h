#pragma once

#include<stdio.h>
#include<vector>
#include<glm\glm.hpp>
#include "Filer.h"

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
	unsigned int m_texture;
	const char* vsSource;
	const char* fsSource;

};


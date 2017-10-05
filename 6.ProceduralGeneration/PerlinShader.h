#pragma once
#include<stdio.h>
#include<vector>
#include<glm/glm.hpp>
#include "PerlinFiler.h"

class PerlinShader
{
public:
	PerlinShader();
	~PerlinShader();

	void bind();
	void unbind();

	void defaultLoad();
	void load(const char * filename, unsigned int type);
	void attach();
	void genPerlinValue();
	void genTextures();

	PerlinFiler* file;
	unsigned int getUniform(const char *);
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int m_program;
	unsigned int m_texture;
	const char* vsSource;
	const char* fsSource;
	float* perlinData;

private:


};


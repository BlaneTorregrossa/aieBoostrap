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

	void load(const char * filename, unsigned int type);
	void attach();
	void genNoiseValue(float width, float height);
	float noise(glm::vec2 pos);
	void genPerlinTextures();

	PerlinFiler* file;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int m_program;
	unsigned int m_texture;
	const char* vsSource;
	const char* fsSource;
	float* perlinData;

};


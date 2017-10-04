#pragma once
#include <stdio.h>
#include <vector>
#include <glm\glm.hpp>
#include "Filer.h"

class Shader
{
public:
	Shader();
	~Shader();

	//virtual bool startup();
	//virtual void shutdown();
	//virtual void update(float);
	//virtual void draw();

	void bind();
	void unbind();

	void defaultload();
	void load(const char * filename, unsigned int type);
	void attach();


	Filer* file;
	unsigned int getUniform(const char *);
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int m_program;
	const char* vsSource;
	const char* fsSource;

private:
	//int success;
};


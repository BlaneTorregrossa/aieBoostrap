#pragma once
#include "Application.h"
#include "_4_DirectLightingApp.h"

#include <gl_core_4_4.h>

class Shader
{
public:
	Shader();
	~Shader();

	virtual bool startup();
	virtual void shutdown();
	virtual void update(float);
	virtual void draw();

	void bind();
	void unbind();

	void defaultload();
	void load(const char * filename, unsigned int type);
	void attach();
	unsigned int getUniform(const char *);

	unsigned int m_program;

	const char* vsSource;
	const char* fsSource;

private:
	unsigned int vertexShader;
	unsigned int fragmentShader;

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
};


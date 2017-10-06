#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>

class _5_TexturesApp : public aie::Application {
public:

	_5_TexturesApp();
	virtual ~_5_TexturesApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

private:

	unsigned int m_texture;
	unsigned int m_program;

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
};
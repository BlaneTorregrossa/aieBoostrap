#pragma once
#include "Application.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>
#include <glm/mat4x4.hpp>
#include <glm\mat3x3.hpp>

#include "Gizmos.h"
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"

class _4_DirectLightingApp : public aie::Application {
public:

	_4_DirectLightingApp();
	~_4_DirectLightingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float);
	virtual void draw();

protected:
	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

private:
	//unsigned int vao;
	//unsigned int vbo;
	//unsigned int ibo;

	Mesh* mesh;
	
	Shader* shader;

};
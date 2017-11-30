#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"

#include <vector>
#include <glm/mat4x4.hpp>

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
	glm::mat4	m_worldMatrix;
	glm::mat4	MODELVIEWPROJECTION;

private:

	Mesh* mesh;
	Shader* shader;

};
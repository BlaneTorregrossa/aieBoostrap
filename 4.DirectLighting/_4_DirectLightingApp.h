#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>

class _4_DirectLightingApp : public aie::Application {
public:

	_4_DirectLightingApp();
	virtual ~_4_DirectLightingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	const char* vsSource;
	const char* fsSource;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};
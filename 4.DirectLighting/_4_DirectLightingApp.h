#pragma once

#include "Application.h"
#include "Gizmos.h"
#include "Input.h"

#include <vector>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>
#include <glm/mat4x4.hpp>
#include <glm\mat3x3.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;

	glm::vec4 normal;
	glm::vec4 tangent;
	glm::vec4 bitangent;
	glm::vec2 texcoord;
};

class _4_DirectLightingApp : public aie::Application {
public:

	_4_DirectLightingApp();
	virtual ~_4_DirectLightingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void generateSphere(unsigned segments, unsigned rings, unsigned& vao, unsigned& vbo, unsigned& ibo, unsigned& indexCount) const;

protected:

	const char* vsSource;
	const char* fsSource;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};
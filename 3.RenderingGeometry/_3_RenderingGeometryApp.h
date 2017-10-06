#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>

class _3_RenderingGeometryApp : public aie::Application {
public:

	_3_RenderingGeometryApp();
	virtual ~_3_RenderingGeometryApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void genPlane();	// function to generate plane 

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	glm::mat4	m_worldMatrix;
	glm::mat4	MODELVIEWPROJECTION;

	Mesh* planeMesh;

	Shader* planeShader;
};
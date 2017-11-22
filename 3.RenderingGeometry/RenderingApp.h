#pragma once
#include "Application.h"
#include "GeoMesh.h"
#include "GeoShader.h"
#include <glm/mat4x4.hpp>

class RenderingApp : public aie::Application
{
public:

	RenderingApp();
	virtual ~RenderingApp();
	
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4	m_worldMatrix;
	glm::mat4	MODELVIEWPROJECTION;

private:
	
	Mesh* planeMesh;
	Mesh* cubeMesh;

	Shader* shader;

};


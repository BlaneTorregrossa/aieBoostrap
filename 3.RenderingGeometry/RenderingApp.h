#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
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

	void generatePlane();

protected:

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

private:
	
	Mesh* planeMesh;

	Shader* planeShader;

};


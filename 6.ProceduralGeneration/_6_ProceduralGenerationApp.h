#pragma once
#include "Application.h"
#include "PerlinMesh.h"
#include "PerlinShader.h"

#include <glm/mat4x4.hpp>

class _6_ProceduralGenerationApp : public aie::Application {
public:

	_6_ProceduralGenerationApp();
	virtual ~_6_ProceduralGenerationApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void genPerlinValue();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

private:

	float* perlinData;

	PerlinMesh* mesh;

	PerlinShader* shader;
};
#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"

#include <glm\mat4x4.hpp>

class Camera;

class CameraApp : public aie::Application
{
public:
	CameraApp();
	virtual ~CameraApp();

	bool startup() override;
	void shutdown() override;
	void update(float) override;
	void draw() override;

protected:

	GLFWwindow* m_window;
	Camera* m_camera;

private:
	
	Mesh* mesh;
	Mesh* meshAlt;

	Shader* shader;

};


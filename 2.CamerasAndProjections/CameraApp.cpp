#include "CameraApp.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Application.h"

#include <vector>
#include <assert.h>
#include <glm\glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace std;
using namespace glm;

CameraApp::CameraApp()
{
}

CameraApp::~CameraApp()
{
}

bool CameraApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.45f);

	mesh = new Mesh();
	meshAlt = new Mesh();
	shader = new Shader();
	m_camera = new Camera();

	m_camera->setLookAt(vec3(50, 50, -50), vec3(0), vec3(1, 1, 1));
	m_camera->setPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	//m_camera->setOrthographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

	m_camera->m_projectionMatrix = m_camera->m_projection;
	m_camera->m_viewMatrix = m_camera->m_view;
	m_camera->MODELVIEWPROJECTION = m_camera->m_projectionMatrix * m_camera->m_viewMatrix;

	shader->load("VertShade.vert", GL_VERTEX_SHADER);
	shader->load("phong.frag", GL_FRAGMENT_SHADER);
	shader->attach();

	mesh->genPlane();
	mesh->Create_buffers();

	meshAlt->genCube();
	meshAlt->Create_buffers();

	return true;
}

void CameraApp::shutdown()
{
}

void CameraApp::update(float deltaTime)
{

}

void CameraApp::draw()
{
	clearScreen();

	glUseProgram(shader->m_program);	// use shader programs

	 //camera bind				 
	int loc = glGetUniformLocation(shader->m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m_camera->MODELVIEWPROJECTION[0][0]);

	// draws
	glBindVertexArray(mesh->m_vao);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindVertexArray(meshAlt->m_vao);
	glDrawElements(GL_TRIANGLES, meshAlt->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);

}

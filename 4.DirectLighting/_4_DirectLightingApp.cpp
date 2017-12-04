#include "_4_DirectLightingApp.h"
#include "Input.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace glm;

_4_DirectLightingApp::_4_DirectLightingApp() {

}

_4_DirectLightingApp::~_4_DirectLightingApp() {

}


bool _4_DirectLightingApp::startup() {

	mesh = new Mesh();
	shader = new Shader();

	// Sets color of the background
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	m_viewMatrix = glm::lookAt(vec3(0, 20, -50), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_worldMatrix = scale(vec3(1));
	MODELVIEWPROJECTION = m_projectionMatrix * m_viewMatrix * m_worldMatrix;

	shader->load("lightVertShade.vert", GL_VERTEX_SHADER);
	shader->load("light.frag", GL_FRAGMENT_SHADER);
	shader->attach();

	mesh->generateSphere(100, 100, mesh->m_vao, mesh->m_vbo, mesh->m_ibo, mesh->index_Count);

	return true;
}

void _4_DirectLightingApp::shutdown() 
{
}

void _4_DirectLightingApp::update(float deltaTime) {

	// time for application running
	float time = getTime();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _4_DirectLightingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	
	glUseProgram(shader->m_program);	// use shader programs

	// camera bind				 
	int loc = glGetUniformLocation(shader->m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MODELVIEWPROJECTION[0][0]);

	//// Get SpecPower Set
	//loc = glGetUniformLocation(shader->m_program, "specularPower");
	//glUniform1f(loc, 0);

	// draws
	glBindVertexArray(mesh->m_vao);
	glDrawElements(GL_TRIANGLES, mesh->index_Count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	glUseProgram(0);
}
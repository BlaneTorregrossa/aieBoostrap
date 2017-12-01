#include "RenderingApp.h"

#include "Gizmos.h"
#include "Input.h"
#include "GeoMesh.h"
#include "GeoShader.h"

#include <vector>
#include <assert.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace std;
using namespace glm;

RenderingApp::RenderingApp() {

}

RenderingApp::~RenderingApp() {

}



// Setup
bool RenderingApp::startup() {

	// new up a mesh
	planeMesh = new Mesh();
	cubeMesh = new Mesh();

	// RGB for background color (soft blue background to make other objects in the window clear to see)
	setBackgroundColour(0.25f, 0.25f, 0.45f);

	// initialise gizmo primitive counts
	//Gizmos::Create();

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(-15, 20, 80), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_worldMatrix = scale(vec3(1));
	MODELVIEWPROJECTION = m_projectionMatrix * m_viewMatrix * m_worldMatrix;

	shader = new Shader();	// new up a shader
	shader->load("VertShade.vert", GL_VERTEX_SHADER);		// Load Vertex Shader from specified file
	shader->load("phong.frag", GL_FRAGMENT_SHADER);		// Load Fragment Shader	from specified file
	shader->attach();	// Attatch both shaders to the program

	planeMesh->genPlane();
	planeMesh->Create_buffers();
	cubeMesh->genCube();
	cubeMesh->Create_buffers();

	return true;
}

void RenderingApp::shutdown() {

	//Gizmos::destroy();
}


void RenderingApp::update(float deltaTime) {

	
}

void RenderingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	glUseProgram(shader->m_program);	// use shader programs
	
	// camera bind				 
	int loc = glGetUniformLocation(shader->m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MODELVIEWPROJECTION[0][0]);

	// draws plane
	glBindVertexArray(planeMesh->m_vao);
	glDrawElements(GL_TRIANGLES, planeMesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// draws cube
	glBindVertexArray(cubeMesh->m_vao);
	glDrawElements(GL_TRIANGLES, cubeMesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}
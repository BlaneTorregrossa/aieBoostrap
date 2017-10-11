#include "_6_ProceduralGenerationApp.h"

#include "Gizmos.h"
#include "Input.h"
#include "PerlinMesh.h"
#include "PerlinShader.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <assert.h>
#include <gl_core_4_4.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

using namespace std;
using namespace glm;

_6_ProceduralGenerationApp::_6_ProceduralGenerationApp() {

}

_6_ProceduralGenerationApp::~_6_ProceduralGenerationApp() {

}

bool _6_ProceduralGenerationApp::startup() {

	mesh = new PerlinMesh();	// new up a mesh

	// RGB for background color (soft blue background to make other objects in the window clear to see)
	setBackgroundColour(0.25f, 0.25f, 0.45f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10, 50, 10), vec3(0), vec3(0, 10, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_worldMatrix = scale(vec3(1));
	MODELVIEWPROJECTION = m_projectionMatrix * m_viewMatrix * m_worldMatrix;


	shader = new PerlinShader();	// new up a shader
	shader->genPerlinValue();		// Generate the values for perlin noise
	shader->genPerlinTextures();	// Setup texture information (Must be done after Perlin value is generated)
	shader->load("perlinVertShade.vert", GL_VERTEX_SHADER);		// Load Vertex Shader from specified file
	shader->load("perlinPhong.frag", GL_FRAGMENT_SHADER);		// Load Fragment Shader	from specified file
	shader->attach();	// Attatch both shaders to the program
	mesh->genPlane();	// Information for geometry to generate a plane
	mesh->Create_buffers();

	return true;
}

void _6_ProceduralGenerationApp::shutdown() {

	Gizmos::destroy();
}

void _6_ProceduralGenerationApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// for camera to move and rotate around the grid
	float time = getTime();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _6_ProceduralGenerationApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	glUseProgram(shader->m_program);

	// camera bind				 
	int loc = glGetUniformLocation(shader->m_program, "projectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MODELVIEWPROJECTION[0][0]);

	// set texture slot (DO NOT REMOVE)
	glActiveTexture(GL_TEXTURE0);	// select active texture unit

	// tell shader where it is 
	loc = glGetUniformLocation(shader->m_program, "perlinTexture");
	glUniform1i(loc, 0);

	// draws
	glBindVertexArray(mesh->m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}





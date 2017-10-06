#include "_3_RenderingGeometryApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

using namespace glm;
using namespace std;

_3_RenderingGeometryApp::_3_RenderingGeometryApp() {

}

_3_RenderingGeometryApp::~_3_RenderingGeometryApp() {

}

bool _3_RenderingGeometryApp::startup() {

	planeMesh = new Mesh();		// new up mesh class for plane
	planeShader = new Shader();	// new up shader class for plane

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_worldMatrix = scale(vec3(1));
	MODELVIEWPROJECTION = m_projectionMatrix * m_viewMatrix * m_worldMatrix;	// "the camera"

	planeShader->load("VertShade.vert", GL_VERTEX_SHADER);	// call load function that takes in "VertShade.vert" shader and declares it's type as a vertex shader
	planeShader->load("phong.frag", GL_FRAGMENT_SHADER);	// call load function that takes in "phong.frag" shader and declares it's type as a fragment shader
	planeShader->attach();	// calls attach function to attach the shaders to the program
	genPlane();	// create plane with given vert and index information
	return true;
}

void _3_RenderingGeometryApp::shutdown() {

	Gizmos::destroy();
}

void _3_RenderingGeometryApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _3_RenderingGeometryApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	planeShader->bind();	// bind shader
	planeMesh->bind();		// bind mesh

	int location = glGetUniformLocation(planeShader->m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, &MODELVIEWPROJECTION[0][0]);

	location = glGetUniformLocation(planeShader->m_program, "diffuse");
	glUniform1i(location, 0);

	glBindVertexArray(planeMesh->m_vao);
	glDrawElements(GL_TRIANGLES, planeMesh->index_Count, GL_UNSIGNED_INT, 0);	// stops here

	planeMesh->unbind();	// unbind mesh
	planeShader->unbind();	// unbind shader
}

void _3_RenderingGeometryApp::genPlane()
{
	Vertex v;

	vector<vec4> positions = {
		vec4(-5, 0, 5, 1),	//v0
		vec4(5, 0, 5, 1),	//v1
		vec4(5, 0,-5, 1),	//v2
		vec4(-5, 0,-5, 1),	//v3
	};

	
	for (int i = 0; i < 4; i++)
	{
		v.position = positions[i];
		planeMesh->m_verticies.push_back(v);
	}

	planeMesh->vertex_Count = planeMesh->m_verticies.size();

	planeMesh->m_indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	planeMesh->index_Count = planeMesh->m_indices.size();

	planeMesh->Create_buffers();
}

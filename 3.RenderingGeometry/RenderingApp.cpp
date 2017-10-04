#include "RenderingApp.h"
#include "Gizmos.h"
#include "Input.h"

#include <vector>
#include<glm\glm.hpp>
#include <glm\ext.hpp>
#include <gl_core_4_4.h>


using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace std;
using namespace glm;

RenderingApp::RenderingApp() : planeMesh(0), planeShader(0)
{
}

RenderingApp::~RenderingApp()
{
}

bool RenderingApp::startup()
{
	
	planeMesh = new Mesh();

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = perspective(quarter_pi<float>(), 16.0f / 9.0f, 0.1f, 1000.0f);

	planeShader = new Shader();
	planeShader->load("VertShade.ver", GL_VERTEX_SHADER);
	planeShader->load("phong.frag", GL_FRAGMENT_SHADER);
	planeShader->attach();



	return false;
}

void RenderingApp::shutdown()
{
}

void RenderingApp::update(float deltaTime)
{
	float time = getTime();
	
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
}

void RenderingApp::draw()
{
	clearScreen();


}

void RenderingApp::generatePlane()
{
	vector<vec4> vertPosition =
	{
		vec4(-5, 0, 5, 1),
		vec4(5, 0, 5, 1),
		vec4(5, 0, -5, 1),
		vec4(-5, 0, -5, 1),
	};

	vector<Vertex> verts;
	for (int i = 0; i != 4; i++)
	{
		Vertex v;
		v.position = vertPosition[i];
		verts.push_back(v);
	}

	vector<unsigned int> indicies =
	{
		0, 1, 2,
		0, 2, 3
	};
};

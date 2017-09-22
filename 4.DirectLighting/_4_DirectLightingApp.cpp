#include "_4_DirectLightingApp.h"
#include "Gizmos.h"
#include "Input.h"

#include <vector>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;
using namespace glm;

_4_DirectLightingApp::_4_DirectLightingApp() : mesh(0) , shader(0) {

}

_4_DirectLightingApp::~_4_DirectLightingApp() {

}

// Need this whole function (NOTE: Can't make any changes to this function!)
void generateSphere(unsigned int segments, unsigned int rings, unsigned int& vao, unsigned int& vbo, unsigned int& ibo, unsigned int& indexCount)
{
	unsigned int vertCount = (segments + 1) * (rings + 2);
	indexCount = segments * (rings + 1) * 6;
	// using AIEVertex for now, but could be any struct as long as it has the correct elements
	Vertex* vertices = new Vertex[vertCount];
	unsigned int* indices = new unsigned int[indexCount];
	float ringAngle = glm::pi<float>() / (rings + 1);
	float segmentAngle = 2.0f * glm::pi<float>() / segments;
	Vertex* vertex = vertices;
	for (unsigned int ring = 0; ring < (rings + 2); ++ring) {
		float r0 = glm::sin(ring * ringAngle);
		float y0 = glm::cos(ring * ringAngle);
		for (unsigned int segment = 0; segment < (segments + 1); ++segment, ++vertex) {
			float x0 = r0 * glm::sin(segment * segmentAngle);
			float z0 = r0 * glm::cos(segment * segmentAngle);
			vertex->position = glm::vec4(x0 * 0.5f, y0 * 0.5f, z0 * 0.5f, 1);
			vertex->normal = glm::vec4(x0, y0, z0, 0);
			vertex->tangent = glm::vec4(glm::sin(segment * segmentAngle + glm::half_pi<float>()), 0, glm::cos(segment * segmentAngle + glm::half_pi<float>()), 0);
			// not a part of the AIEVertex, but this is how w generate bitangents
			vertex->bitangent = glm::vec4(glm::cross(glm::vec3(vertex->normal), glm::vec3(vertex->tangent)), 0);
			vertex->texcoord = glm::vec2(segment / (float)segments, ring / (float)(rings + 1));
		}
	}
	unsigned int index = 0;
	for (unsigned i = 0; i < (rings + 1); ++i) {
		for (unsigned j = 0; j < segments; ++j) {
			indices[index++] = i * (segments + 1) + j;
			indices[index++] = (i + 1) * (segments + 1) + j;
			indices[index++] = i * (segments + 1) + (j + 1);
			indices[index++] = (i + 1) * (segments + 1) + (j + 1);
			indices[index++] = i * (segments + 1) + (j + 1);
			indices[index++] = (i + 1) * (segments + 1) + j;
		}
	}
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	// generate vertex array object (descriptors)
	glGenVertexArrays(1, &vao);
	// all changes will apply to this handle
	glBindVertexArray(vao);
	// set vertex buffer data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	// index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));
	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));
	// texcoords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3));
	// tangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3 + sizeof(glm::vec2)));
	// safety
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] indices;
	delete[] vertices;
}

bool _4_DirectLightingApp::startup() {

	mesh = new Mesh();
	shader = new Shader();

	// Sets color of the background
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	//shader->defaultload();

	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::quarter_pi<float>(), 16.0f / 9.0f, 0.1f, 1000.0f);
	shader->load("VertShade.vert", GL_VERTEX_SHADER);
	shader->load("phong.frag", GL_FRAGMENT_SHADER);
	shader->attach();
	generateSphere(16, 16, mesh->m_vao, mesh->m_vbo, mesh->m_ibo, mesh->index_Count);

	return true;
}

void _4_DirectLightingApp::shutdown() {

	Gizmos::destroy();
}

void _4_DirectLightingApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// time for application running
	float time = getTime();

	// a camera's movement to give a good enough view to observe an object positioned in the center
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 20, 5, glm::cos(time) * 15), vec3(0), vec3(0, 1, 0));

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1), 25);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _4_DirectLightingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	
	shader->bind();
	mesh->bind();
	
	int projView = shader->getUniform("projectionView");
	glUniformMatrix4fv(projView, 1, false, &m_projectionMatrix[0][0]);

	//glUseProgram(shader->m_program);
	glDrawElements(GL_TRIANGLES, mesh->index_Count, GL_UNSIGNED_INT, 0);

	
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	mesh->unbind();
	shader->unbind();
}
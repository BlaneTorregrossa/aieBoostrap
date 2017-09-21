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

_4_DirectLightingApp::_4_DirectLightingApp() {

}

_4_DirectLightingApp::~_4_DirectLightingApp() {

}

#pragma region Good as is
bool _4_DirectLightingApp::startup() {

	// From guide from last wednesday/thursday (vsSource & fsSource)

	vsSource = "#version 410\n \
				in vec4 Position; \
				in vec4 Colour; \
				out vec4 vColour; \
				out vec4 vPosition; \
				uniform mat4 ProjectionView; \
				void main() { \
				vColour = Colour; vPosition = Position; \
				gl_Position = ProjectionView * Position; }";

	fsSource = "#version 410\n \
				in vec4 vColour; \
				in vec4 vPosition; \
				out vec4 FragColor; \
				uniform vec3 LightDir; \
				uniform vec3 LightColour; \
				uniform vec3 CameraPos; \
				uniform float SpecPow; \
				void main() { float d = max(0, dot ( normalize(vNormal.xyz), LightDir ) );\
				vec3 E = normalize ( CameraPos - vPosition.xyz ); \
				vec3 R = reflect ( -LightDir, vNormal.xyz ); \
				float s = max (0, dot( E, R ) ); \
				s = pow( s, SpecPow ); \
				FragColor = vec4( LightColour * d + LightColour * s, 1); }";

	// Sets color of the background
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.60f, 16.0f / 9.0f, 0.1f, 1000.0f);

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
	Gizmos::addTransform(mat4(1));

	// objects in window
	

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _4_DirectLightingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}
#pragma endregion

// Need this whole function (NOTE: Can't make any changes to this class!)
void _4_DirectLightingApp::generateSphere(unsigned segments, unsigned rings, unsigned & vao, unsigned & vbo, unsigned & ibo, unsigned & indexCount) const
{
	unsigned int vertCount = (segments + 1) * (rings + 2);
	indexCount = segments * (rings + 1) * 6;

	// using AIEVertex for now, but could be any struct as long as it has the correct elements
	Vertex* vertices = new Vertex[vertCount];
	unsigned int* indices = new unsigned int[indexCount];

	float ringAngle = pi<float>() / (rings + 1);
	float segmentAngle = 2.0f * pi<float>() / segments;

	Vertex* vertex = vertices;

	for (unsigned int ring = 0; ring < (rings + 2); ++ring)
	{
		float r0 = sin(ring * ringAngle);
		float y0 = cos(ring * ringAngle);

		for (unsigned int segment = 0; segment < (segments + 1); ++segment, ++vertex)
		{
			float x0 = r0 * sin(segment * segmentAngle);
			float z0 = r0 * cos(segment * segmentAngle);

			vertex->position = vec4(x0 * 0.5f, y0 * 0.5f, z0 * 0.5f, 1);
			vertex->normal = vec4(x0, y0, z0, 0);

			vertex->tangent = vec4(sin(segment * segmentAngle + half_pi<float>()), 0, cos(segment * segmentAngle + half_pi<float>()), 0);

			// not a part of the AIEVertex, but this is how we generate bitangents 
			vertex->bitangent = vec4(cross(vec3(vertex->normal), vec3(vertex->tangent)), 0);

			vertex->texcoord = vec2(segment / (float)segments, ring / (float)(rings + 1));
		}
	}

	unsigned int index = 0;
	for (unsigned i = 0; i < (rings + 1); ++i)
	{
		for (unsigned j = 0; j < segments; ++j)
		{
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(vec4) * 2));

	// texcoords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) * 3));

	// tangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(vec4) * 3 + sizeof(vec2)));

	// safety  (Unbinds vao, vbo, ibo)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indices;
	delete[] vertices;
}


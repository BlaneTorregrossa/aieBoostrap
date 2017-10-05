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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

using namespace std;
using namespace glm;

//struct Vertex
//{
//	vec4 position;
//	vec2 uv;
//};

_6_ProceduralGenerationApp::_6_ProceduralGenerationApp() {

}

_6_ProceduralGenerationApp::~_6_ProceduralGenerationApp() {

}

bool _6_ProceduralGenerationApp::startup() {

	mesh = new PerlinMesh();

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(5, 10, 5), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	shader = new PerlinShader();	
	shader->genPerlinValue();
	shader->genTextures();
	shader->load("perlinVertShade.vert", GL_VERTEX_SHADER);
	shader->load("perlinPhong.frag", GL_FRAGMENT_SHADER);
	shader->attach();
	mesh->genPlane();
	mesh->Create_buffers();

#pragma region load shader
//	const char* vsSource = "#version 410\n \
// layout(location=0) in vec4 position; \
// layout(location=1) in vec2 texCoord; \
// uniform mat4 projectionView; \
// out vec2 vTexCoord; \
// void main() { \
// vTexCoord = texCoord; \
// gl_Position = projectionView * position; \
// }";
//
//	const char* fsSource = "#version 410\n \
//in vec2 vTexCoord; \
//out vec4 fragColor; \
//uniform sampler2D perlinTexture; \
//void main() { \
//fragColor = texture(perlinTexture, vTexCoord).rrrr; }";
//
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
//	glCompileShader(vertexShader);
//	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
//	glCompileShader(fragmentShader);
//
#pragma endregion

#pragma region attach shader
	//m_program = glCreateProgram();
	//glAttachShader(m_program, vertexShader);
	//glAttachShader(m_program, fragmentShader);
	//glLinkProgram(m_program);

	//int success = GL_FALSE;
	//glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	//if (success == GL_FALSE) {
	//	int infoLogLength = 0;
	//	glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength); char* infoLog = new char[infoLogLength];
	//	glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
	//	printf("Error: Failed to link shader program!\n"); printf("%s\n", infoLog); delete[] infoLog;
	//}

#pragma endregion

#pragma region plane

	//vector<vec4> positions = {
	//	vec4(-5, 0, 5, 1),	//v0
	//	vec4(5, 0, 5, 1),	//v1
	//	vec4(5, 0, -5, 1),	//v2
	//	vec4(-5, 0, -5, 1),	//v3
	//};

	//vector<vec2> uvs = {
	//	vec2(0,1), //tl v0
	//	vec2(0,0), //tr v1
	//	vec2(1,0), //br v2
	//	vec2(1,1)  //bl v3
	//};
	//vector<Vertex> verts;
	//for (int i = 0; i < 4; i++)
	//{
	//	Vertex v;
	//	v.position = positions[i];
	//	v.uv = uvs[i];
	//	verts.push_back(v);
	//}
	//vector<unsigned> indices =
	//{
	//	0,1,2,
	//	0,2,3
	//};
#pragma endregion

#pragma region createBuffers
	/*glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof vec4, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof vec2, (void*)sizeof(vec4));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); */
#pragma endregion

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

	//// draw a simple grid with gizmos
	//vec4 white(1);
	//vec4 black(0, 0, 0, 1);
	//for (int i = 0; i < 21; ++i) {
	//	Gizmos::addLine(vec3(-10 + i, 0, 10),
	//		vec3(-10 + i, 0, -10),
	//		i == 10 ? white : black);
	//	Gizmos::addLine(vec3(10, 0, -10 + i),
	//		vec3(-10, 0, -10 + i),
	//		i == 10 ? white : black);
	//}

	//// add a transform so that we can see the axis
	//Gizmos::addTransform(mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _6_ProceduralGenerationApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	shader->bind();
	mesh->bind();

	auto m_worldMatrix = scale(vec3(1.0f));
	auto MODELVIEWPROJECTION = m_projectionMatrix * m_viewMatrix * m_worldMatrix;

	// camera bind
	int loc = shader->getUniform("projectionView");
	glUniformMatrix4fv(loc, 1, false, &MODELVIEWPROJECTION[0][0]);

	// set texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shader->m_texture);

	// tell shader where it is
	loc = glGetUniformLocation(shader->m_program, "perlinTexture");
	glUniform1i(loc, 0);

	// draws
	glBindVertexArray(mesh->m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	mesh->unbind();
	shader->unbind();
}

void _6_ProceduralGenerationApp::genPerlinValue()
{
	//int dims = 512; // must be the product of the power of 2
	//perlinData = new float[dims * dims];
	//float scale = (1.0f / dims) * 3;
	//int octaves = 6;

	//for (int x = 0; x < 512; ++x)
	//{
	//	for (int y = 0; y < 512; ++y)
	//	{
	//		float amplitude = 1.f;
	//		float persistence = 0.3f;
	//		perlinData[y * dims + x] = 0;
	//	}
	//}
}

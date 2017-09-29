#include "_5_TexturesApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

using namespace glm;

_5_TexturesApp::_5_TexturesApp() {

}

_5_TexturesApp::~_5_TexturesApp() {

}

bool _5_TexturesApp::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(0,0,10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	int imageWidth, imageHeight, imageFormat;
	unsigned char* data = stbi_load("./textures/crate.png", &imageWidth, &imageHeight, &imageFormat, STBI_default);

	glGenTextures(1, &m_texture);	// used to generate many texture handles at once
	glBindTexture(GL_TEXTURE_2D, m_texture);	// bind the textures to the correct slot
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	// speciy the data for the texture (format, resolution and variable type). 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);	// free the loaded data of the texture


#pragma region load shader
	const char* vsSource = "#version 410\n \
							 layout(location=0) in vec4 position; \
							 layout(location=1) in vec2 texCoord; \
							 out vec2 vTexCoord; \
							 uniform mat4 projectionViewWorldMatrix; \
							 void main() { \
							 vTexCoord = texCoord; \
							 gl_Position = projectionViewWorldMatrix * position; \
							 }";

	const char* fsSource = "#version 410\n \
							in vec2 vTexCoord; \
							out vec4 fragColor; \
							uniform sampler2D diffuse; \
							void main() { \
							fragColor = texture(diffuse,vTexCoord); \
							}";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

#pragma region attach shader
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
#pragma endregion

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
#pragma endregion


#pragma region plane
	float vertexData[] =
	{
		-1, 0, 1, 1,		 0, 1,
		1, 0, 1, 1,			1, 1,
		1, 0, -1, 1,		1, 0,
		-1, 0, -1, 1,		0, 0,
	};

	unsigned int indexData[] =
	{
		0, 1, 2,
		0, 2, 3,
	};
#pragma endregion

#pragma region createBuffers
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(6 * sizeof(float)));

	//cleanup
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion

	return true;
}

void _5_TexturesApp::shutdown() {

	Gizmos::destroy();
}

void _5_TexturesApp::update(float deltaTime) {

	//// wipe the gizmos clean for this frame
	//Gizmos::clear();

	//// for camera to move and rotate around the grid
	//float time = getTime();
	//m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 20, 5, glm::cos(time) * 15), vec3(0), vec3(0, 1, 0));

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

	//// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _5_TexturesApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// for drawing
	glUseProgram(m_program); // use texture program

	// camera bind
	int loc = glGetUniformLocation(m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m_projectionMatrix[0][0]);
 
	loc = glGetUniformLocation(m_program, "diffuse");
	glUniform1i(loc, 0);

	// set texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// draws
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}
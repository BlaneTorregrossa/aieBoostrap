#include "_6_ProceduralGenerationApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
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

struct Vertex 
{
	vec4 position;
	vec2 uv;
};

_6_ProceduralGenerationApp::_6_ProceduralGenerationApp() {

}

_6_ProceduralGenerationApp::~_6_ProceduralGenerationApp() {

}

bool _6_ProceduralGenerationApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	int imageWidth, imageHeight, imageFormat;
	unsigned char* data = stbi_load("./textures/crate.png", &imageWidth, &imageHeight, &imageFormat, 0);

	glGenTextures(1, &m_texture);	// used to generate many texture handles at once
	glBindTexture(GL_TEXTURE_2D, m_texture);	// bind the textures to the correct slot
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	// speciy the data for the texture (format, resolution and variable type). 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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
fragColor = texture(diffuse,vTexCoord);}";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

#pragma endregion

#pragma region attach shader
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	int success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength); char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n"); printf("%s\n", infoLog); delete[] infoLog;
	}

#pragma endregion


#pragma region plane
	/*float vertexData[] =
	{ -5, 0, 5, 1,		0, 1,
	5, 0, 5, 1,		1, 1,
	5, 0, -5, 1,    1, 0,
	-5, 0, -5, 1, 	0, 0, };
	unsigned int indexData[] =
	{
	0, 1, 2,
	0, 2, 3,
	};*/

	vector<vec4> positions = {
		vec4(-5, 0, 5, 1),	//v0
		vec4(5, 0, 5, 1),	//v1
		vec4(5, 0,-5, 1),	//v2
		vec4(-5, 0,-5, 1),	//v3
	};

	vector<vec2> uvs = {
		vec2(0,1), //tl v0
		vec2(0,0), //tr v1
		vec2(1,0), //br v2
		vec2(1,1)  //bl v3
	};
	vector<Vertex> verts;
	for (int i = 0; i < 4; i++)
	{
		Vertex v;
		v.position = positions[i];
		v.uv = uvs[i];
		verts.push_back(v);
	}
	vector<unsigned> indices =
	{
		0,1,2,
		0,2,3
	};
#pragma endregion

#pragma region createBuffers
	glGenVertexArrays(1, &m_vao);
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

	//// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _6_ProceduralGenerationApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// for drawing
	glUseProgram(m_program); // use texture program

	auto m_worldMatrix = scale(vec3(1));
	auto MODELVIEWPROJECTION = m_projectionMatrix * m_viewMatrix * m_worldMatrix;

	// camera bind
	int loc = glGetUniformLocation(m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &MODELVIEWPROJECTION[0][0]);

	// set texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// tell shader where it is
	loc = glGetUniformLocation(m_program, "diffuse");
	glUniform1i(loc, 0);

	// draws
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


}

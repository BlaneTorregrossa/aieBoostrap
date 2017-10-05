#include "PerlinMesh.h"

#include <vector>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <assert.h>
#include <gl_core_4_4.h>



using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace std;
using namespace glm;

PerlinMesh::PerlinMesh()
{
}


PerlinMesh::~PerlinMesh()
{
}

void PerlinMesh::genPlane()
{
	vector<vec4> positions = {
		vec4(-5, 0, 5, 1),	//v0
		vec4(5, 0, 5, 1),	//v1
		vec4(5, 0, -5, 1),	//v2
		vec4(-5, 0, -5, 1),	//v3
	};

	vector<vec2> uvs = {
		vec2(0,1), //tl v0
		vec2(0,0), //tr v1
		vec2(1,0), //br v2
		vec2(1,1)  //bl v3
	};
	for (int i = 0; i < 4; i++)
	{
		Vertex v;
		v.position = positions[i];
		v.uv = uvs[i];
		verts.push_back(v);
	}

	indices =
	{
		0,1,2,
		0,2,3
	};
}

void PerlinMesh::Create_buffers()
{

	glGenVertexArrays(1, &m_vao);

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
}

void PerlinMesh::initialize(std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	for (auto v : verts)
	{
		verts.push_back(v);
	}

	for (auto i : indices)
	{
		indices.push_back(i);
	}

	index_Count = indices.size();
	vertex_Count = verts.size();
}

void PerlinMesh::bind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void PerlinMesh::unbind()
{
	glBindVertexArray(m_vao);
}

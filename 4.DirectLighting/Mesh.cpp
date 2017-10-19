#include "Mesh.h"

#include <vector>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <gl_core_4_4.h>

using std::vector;
using glm::vec3;
using glm::vec4;
using glm::mat4;

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::genPlane()
{
	positions = {
		vec4(0, 0, 0, 1),	//v2 BOTTOM LEFT
		vec4(5, 0, 0, 1),	//v3 BOTTOM RIGHT
		vec4(5, 0, 5, 1),	//v1 TOP RIGHT
		vec4(0, 0, 5, 1),	//v0 TOP LEFT	
	};

	//	Verticies information
	for (int i = 0; i < 4; i++)
	{
		Vertex v;
		v.position = positions[i];
		verts.push_back(v);
	}

	//	Indicies information
	indices =
	{
		0,1,3,
		3,2,1
	};
}

void Mesh::genCube()
{
	positions = {
		vec4(0, 0, 0, 1),	//BOTTOM LEFT
		vec4(5, 0, 0, 1),	//BOTTOM RIGHT
		vec4(5, 5, 0, 1),	//TOP RIGHT
		vec4(0, 5, 0, 1),	//TOP LEFT	
		
		vec4(0, 0, -5, 1),	//BOTTOM LEFT
		vec4(5, 0, -5, 1),	//BOTTOM RIGHT
		vec4(5, 5, -5, 1),	//TOP LEFT
		vec4(0, 5, -5, 1),	//TOP LEFT


	};

	//	Verticies information
	for (int i = 0; i < 8; i++)
	{
		Vertex v;
		v.position = positions[i];
		verts.push_back(v);
	}

}

void Mesh::Create_buffers()
{
	//	bind vertex array object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//	vertex buffer object
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

	//	index buffer object
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);		// You see that Vertex? That stays as Vertex

	//cleanup
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

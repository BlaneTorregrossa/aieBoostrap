#include "Mesh.h"

#include <gl_core_4_4.h>
Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::Create_buffers()
{
	//generate buffers
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	//vertex array object
	glGenVertexArrays(1, &m_vao);
	//set vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_Count * sizeof(Vertex), m_verticies.data(), GL_STATIC_DRAW);
	//set index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_Count * sizeof(unsigned), m_indices.data(), GL_STATIC_DRAW);
	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	// normal
	// color
	// textures/uv

}

void Mesh::bind()
{
	glBindVertexArray(m_vao);	// bind vertex array
}

void Mesh::unbind()
{
	glBindVertexArray(0);	// unbind vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// unbind vertex buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// unbind index buffer object
}


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
	//generatte vertex array object
	glGenVertexArrays(1, &m_vao);
	//set vertex buffer data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_Count * sizeof(Vertex), m_verticies.data(), GL_STATIC_DRAW);
	//set index buffer data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_Count * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

}

void Mesh::initialize(std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	for (auto v : verts)
	{
		m_verticies.push_back(v);
	}

	for (auto i : indices)
	{
		m_indices.push_back(i);
	}

	index_Count = m_indices.size();
	vertex_Count = m_verticies.size();
}

void Mesh::bind()
{
	glBindVertexArray(m_vao);	
}

void Mesh::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


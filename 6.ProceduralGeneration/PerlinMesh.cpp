#include "PerlinMesh.h"

#include <vector>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
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

// generate a plane from given vectors
void PerlinMesh::genPlane()
{
	positions = {
		vec4(0, 0, 0, 1),	//v2 BOTTOM LEFT
		vec4(5, 0, 0, 1),	//v3 BOTTOM RIGHT
		vec4(5, 0, 5, 1),	//v1 TOP RIGHT
		vec4(0, 0, 5, 1),	//v0 TOP LEFT	
	};

	uvs = {
		vec2(1,1), //tl v0
		vec2(1,0), //tr v1
		vec2(0,0), //br v2
		vec2(0,1)  //bl v3
	};

	//	Verticies information
	for (int i = 0; i < 4; i++)
	{
		Vertex v;
		v.position = positions[i];
		v.uv = uvs[i];
		verts.push_back(v);
	}

	//	Indicies information
	indices =
	{
		0,1,3,
		3,2,1
	};
}

void PerlinMesh::generateGrid(unsigned int rows, unsigned int cols)
{
	auto aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			Vertex vert = {
				vec4(float(c), 0, float(r), 1), //POSITION
				vec2(float(c) / float(cols - 1), float(r) / float(rows - 1)), //TEXTURE COORDINATE				
			};
			aoVertices[r * cols + c] = vert;
		}
	}

	//Defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//Triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			//Triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	for (unsigned int i = 0; i < (rows * cols); i++)
	{
		verts.push_back(aoVertices[i]);
	}

	for (unsigned int i = 0; i < index; i++)
	{
		indices.push_back(auiIndices[i]);
	}

	delete[] aoVertices;
	delete[] auiIndices;
}

void PerlinMesh::Create_buffers()
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
	
	//uv
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec4));	// Same for this one
	
	//cleanup
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
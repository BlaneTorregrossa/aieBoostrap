#pragma once
#include <vector>
#include<glm\glm.hpp>

struct Vertex
{
	glm::vec4 position;
};

class Mesh 
{
public: 
	Mesh();
	~Mesh();

	void Create_buffers();
	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);
	void bind();
	void unbind();

	unsigned int index_Count;
	unsigned int vertex_Count;

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	
	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_verticies;
};


#pragma once
#include <vector>
#include<glm/glm.hpp>

struct Vertex
{
	glm::vec4 position;
	glm::vec2 uv;
};

class PerlinMesh
{
public:
	PerlinMesh();
	~PerlinMesh();

	void genPlane();
	void Create_buffers();
	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);
	void bind();
	void unbind();

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

protected:

	std::vector<Vertex> verts;
	std::vector<unsigned> indices;

	unsigned int index_Count;
	unsigned int vertex_Count;

private:


};


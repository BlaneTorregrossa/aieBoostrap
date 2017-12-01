#pragma once

#include <vector>
#include <glm\glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

struct Vertex
{
	vec4 position;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void genPlane();
	void genCube();
	void Create_buffers();

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	std::vector<Vertex> verts;
	std::vector<unsigned> indices;

	std::vector<vec4> positions;
	std::vector<vec2> uvs;

protected:

	unsigned int index_Count;
	unsigned int vertex_Count;
};


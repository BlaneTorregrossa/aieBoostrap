#pragma once
#include <vector>
#include<glm\glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;

	glm::vec4 normal;
	glm::vec4 tangent;
	glm::vec4 bitangent;
	glm::vec2 texcoord;
};

class Mesh 
{
public: 
	Mesh();
	~Mesh();

	void Create_buffers();
	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);
		
	void generateSphere(unsigned int segments, unsigned int rings, unsigned int& vao, unsigned int& vbo, unsigned int& ibo, unsigned int& indexCount);
	


	unsigned int index_Count;
	unsigned int vertex_Count;

	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_verticies;

	std::vector<vec4> positions;
	std::vector<vec4> colours;
	std::vector<vec4> normals;
	std::vector<vec4> tangents;
	std::vector<vec4> bitangents;
	std::vector<vec2> texcoords;

protected:

};


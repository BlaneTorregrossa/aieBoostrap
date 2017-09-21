#pragma once
#include "Application.h"
#include "Gizmos.h"
#include "_4_DirectLightingApp.h"

#include <vector>
#include <Gizmos.h>
#include<glm\glm.hpp>
#include <gl_core_4_4.h>

//What I previously had
//struct Vertex
//{
//	glm::vec4 position;
//	glm::vec4 colour;
//};

class Mesh : aie::Gizmos
{
public:
	//Mesh();
	~Mesh();

	void Create_buffers();
	void initialize(std::vector<GizmoVertex>&verts, std::vector<unsigned int>&indices);
	void bind();
	void unbind();
	
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float);
	virtual void draw();

	unsigned int index_Count;
	unsigned int vertex_Count;
	
private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	std::vector<unsigned int> m_indices;
	std::vector<GizmoVertex> m_verticies;
};


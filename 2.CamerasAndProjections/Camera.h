#pragma once
#include "gl_core_4_4.h"
#include<glm\mat4x4.hpp>
#include<glm\vec3.hpp>

using glm::vec4;
using glm::mat4;

using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	void setPerspective(float fov, float aspectRatio, float Near, float Far);
	void setOrthographic(float left, float right, float bottom, float top, float Near, float Far);

	void setLookAt(vec3 eye, vec3 center, vec3 up);

	void Rotate();

	mat4	m_viewMatrix;
	mat4	m_projectionMatrix;
	mat4	m_worldMatrix;
	mat4	MODELVIEWPROJECTION;

	mat4 m_world;
	mat4 m_view;
	mat4 m_projection;
	mat4 m_viewProjection;
	mat4 m_position;

private:
	float m_fov; float m_aspectRatio;
	float m_near; float m_far;
	float m_top; float m_bottom;
	float m_left; float m_right;


};


#include "Camera.h"

#include "Input.h"

#include <assert.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>


Camera::Camera()
{
}


Camera::~Camera()
{
}



void Camera::setPerspective(float fov, float aspectRatio, float Near, float Far)
{
	float x = 1.f / (aspectRatio * tan(fov / 2.f));
	float y = 1.f / tan(fov / 2.f);
	float z = -((Far + Near) / (Far - Near));
	float w = -(2.f * (Far * Near) / (Far - Near));

	mat4 P = mat4(
		vec4(x, 0, 0, 0),
		vec4(0, y, 0, 0),
		vec4(0, 0, z, -1),
		vec4(0, 0, w, 0)
	);

	mat4 test = glm::perspective(fov, aspectRatio, Near, Far);
	assert(test == P);
	m_projection = P;

}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up)
{
	vec3 z = normalize(eye - center);
	vec3 x = normalize(cross(up, z));
	vec3 y = cross(z, x);

	// view
	mat4 V = mat4(
		vec4(x.x, y.x, z.x, 0),
		vec4(x.y, y.y, z.y, 0),
		vec4(x.z, y.z, z.z, 0),
		vec4(0, 0, 0, 1)
	);

	// translation
	mat4 T = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-eye.x, -eye.y, -eye.z, 1)
	);
	m_view = V * T;
	mat4 m_lookAtTest = glm::lookAt(eye, center, up);
	assert(m_view == m_lookAtTest);
}

void Camera::Rotate()
{
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float Near, float Far)
{
	float X = 2 / (right - left);
	float Y = 2 / (top - bottom);
	float Z = -2 / (Far - Near);

	float WX = -((right + left) / (right - left));
	float WY = -((top + bottom) / (top - bottom));
	float WZ = -((Far + Near) / (Far - Near));

	// Original setup had two matracies, shown itself as a waste and inconsistent

	mat4 O = mat4(
		vec4(X, 0, 0, 0),
		vec4(0, Y, 0, 0),
		vec4(0, 0, Z, 0),
		vec4(WX, WY, WZ, 1)
	);

	m_projection = O;
	mat4 test = ortho(left, right, bottom, top, Near, Far);
	assert(m_projection == test);

}

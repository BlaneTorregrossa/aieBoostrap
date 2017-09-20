#include "_4_DirectLightingApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

_4_DirectLightingApp::_4_DirectLightingApp() {

}

_4_DirectLightingApp::~_4_DirectLightingApp() {

}

bool _4_DirectLightingApp::startup() {
	
	// From guide from last wednesday/thursday (vsSource & fsSource)

	vsSource = "#version 410\n \
				in vec4 Position; \
				in vec4 Colour; \
				out vec4 vColour; \
				out vec4 vPosition; \
				uniform mat4 ProjectionView; \
				void main() { \
				vColour = Colour; vPosition = Position; \
				gl_Position = ProjectionView * Position; }";

	fsSource = "#version 410\n \
				in vec4 vColour; \
				in vec4 vPosition \
				out vec4 FragColor; \
				uniform vec3 LightDir; \
				uniform vec3 LightColour; \
				uniform vec3 CameraPos; \
				uniform float SpecPow; \
				void main() { float d = max(0, dot ( normalize(vNormal.xyz), LightDir ) );\
				vec3 E = normalize ( CameraPos - vPosition.xyz ); \
				vec3 R = reflect ( -LightDir, vNormal.xyz ); \
				float s = max (0, dot,( E, R ) ); \
				s = pow( s, SpecPow ); \
				FragColor = vec4( LightColour * d + LightColour * s, 1); }";

	// Sets color of the background
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.60f, 16.0f / 9.0f, 0.1f, 1000.0f);

	return true;
}

void _4_DirectLightingApp::shutdown() {

	Gizmos::destroy();
}

void _4_DirectLightingApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// time for application running
	float time = getTime();

	// a camera's movement to give a good enough view to observe an object positioned in the center
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time) * 20, 5, glm::cos(time) * 15), vec3(0), vec3(0, 1, 0));

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// shapes
	Gizmos::addSphere(vec3(0, 3, 0), 3, 16, 16, vec4(.50f, .50f, .50f, 1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _4_DirectLightingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}
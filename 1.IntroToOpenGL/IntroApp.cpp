#include "IntroApp.h"



IntroApp::IntroApp()
{
}


IntroApp::~IntroApp()
{
}

void IntroApp::run(const char * title, unsigned int width, unsigned int height, bool fullscreen)
{
	Application::run(title, width, height, fullscreen);
}

bool IntroApp::startup()
{
	return true;
}

void IntroApp::shutdown()
{
}

void IntroApp::update(float)
{
}

void IntroApp::draw()
{
}

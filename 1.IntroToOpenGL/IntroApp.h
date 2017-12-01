#pragma once
#include "Application.h"

class IntroApp : public aie::Application
{
public:
	IntroApp();
	~IntroApp();

	void run(const char* title, unsigned int width, unsigned int height, bool fullscreen);

	virtual bool startup();
	virtual void shutdown();
	virtual void update(float);
	virtual void draw();
};


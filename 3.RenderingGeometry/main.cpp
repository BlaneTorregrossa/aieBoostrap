#include "RenderingApp.h"

int main()
{

	auto app = new RenderingApp();

	app->run("Render planesand a sphere", 1280, 720, false);

	delete app;

	return 0;
}
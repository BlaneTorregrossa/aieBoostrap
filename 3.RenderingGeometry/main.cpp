#include "_3_RenderingGeometryApp.h"

int main() {
	
	// allocation
	auto app = new _3_RenderingGeometryApp();

	// initialise and loop
	app->run("Please work", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
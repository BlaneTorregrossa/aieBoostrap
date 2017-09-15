#include "_4_DirectLightingApp.h"

int main() {
	
	// allocation
	auto app = new _4_DirectLightingApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
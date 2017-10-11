#include "_6_ProceduralGenerationApp.h"

int main() {
	
	// allocation
	auto app = new _6_ProceduralGenerationApp();

	// initialise and loop
	app->run("NOISE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
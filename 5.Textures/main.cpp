#include "_5_TexturesApp.h"

int main() {
	
	// allocation
	auto app = new _5_TexturesApp();

	// initialise and loop
	app->run("Texture", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
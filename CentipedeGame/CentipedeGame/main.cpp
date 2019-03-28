#include "CentipedeGameApp.h"

int main() {
	
	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("Centipede", 720, 900, false);

	// deallocation
	delete app;

	return 0;
}
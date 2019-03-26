#include "CentipedeGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

CentipedeGameApp::CentipedeGameApp() {

}

CentipedeGameApp::~CentipedeGameApp() {

}

bool CentipedeGameApp::startup() {
	
	renderer = new Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	font = new Font("../bin/font/consolas.ttf", 32);

	return true;
}

void CentipedeGameApp::shutdown() {

	delete font;
	delete renderer;
}

void CentipedeGameApp::update(float deltaTime) {

	//Get Input Instance
	Input* input = Input::getInstance();

	// exit the application
	if (input->isKeyDown(INPUT_KEY_ESCAPE))
		quit();
}

void CentipedeGameApp::draw() {

	//Clear the screen
	clearScreen();

	//Begin drawing sprites
	renderer->begin();

	//Draw...

	//Done drawing sprites
	renderer->end();
}
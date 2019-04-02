#include "CentipedeGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "GameScene.h"

CentipedeGameApp* CentipedeGameApp::instance = nullptr;

CentipedeGameApp::CentipedeGameApp() 
{
	CentipedeGameApp::instance = this;
}

CentipedeGameApp::~CentipedeGameApp() 
{

}

bool CentipedeGameApp::startup() 
{
	renderer = new Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	font = new Font("../bin/font/consolas.ttf", 32);

	shipTexture = new Texture("./textures/ship.png");
	bulletTexture = new Texture("./textures/bullet.png");

	currentScene = nullptr;
	gameScene = new GameScene(shipTexture);
	
	ChangeScene(gameScene);

	return true;
}

void CentipedeGameApp::shutdown()
{
	delete font;
	delete renderer;
	delete shipTexture;
	delete bulletTexture;
}

void CentipedeGameApp::update(float deltaTime) 
{
	//Get Input Instance
	Input* input = Input::getInstance();

	if (currentScene != nullptr)
		currentScene->Update(deltaTime, input);

	//Exit the application
	if (input->isKeyDown(INPUT_KEY_ESCAPE))
		quit();
}

void CentipedeGameApp::draw() 
{
	//Clear the screen
	clearScreen();

	//Begin drawing sprites
	renderer->begin();

	//Draw...
	if (currentScene != nullptr)
		currentScene->Draw(renderer);

	//Done drawing sprites
	renderer->end();
}

void CentipedeGameApp::ChangeScene(Scene* newScene)
{
	if (newScene == nullptr)
		return;

	if (currentScene != nullptr)
		currentScene->OnClose();
	currentScene = newScene;
	currentScene->OnStart();
}
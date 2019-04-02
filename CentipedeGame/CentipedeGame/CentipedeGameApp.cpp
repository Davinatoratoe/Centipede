#include "CentipedeGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "GameScene.h"
#include "ListScene.h"
#include "MenuScene.h"
#include "BinaryTreeScene.h"
#include "LinkedListScene.h"

//Initialise the static instance variable
CentipedeGameApp* CentipedeGameApp::instance = nullptr;

/// <summary>
/// Default constructor.
/// </summary>
CentipedeGameApp::CentipedeGameApp() 
{
	//Set the static instance variable to this instance
	CentipedeGameApp::instance = this;
}

/// <summary>
/// Deconstructor.
/// </summary>
CentipedeGameApp::~CentipedeGameApp() 
{

}

/// <summary>
/// Called when the application starts.
/// </summary>
/// <returns>True if the application loaded correctly successfully.</returns>
bool CentipedeGameApp::startup() 
{
	//Create the Renderer
	renderer = new Renderer2D();

	//Load the font(s)
	font = new Font("../bin/font/consolas.ttf", 30);

	//Load the texture(s)
	shipTexture = new Texture("./textures/ship.png");
	bulletTexture = new Texture("./textures/bullet.png");

	//Load the scenes(s)
	currentScene = nullptr;
	gameScene = new GameScene(shipTexture);
	menuScene = new MenuScene(font);
	listScene = new ListScene(font);
	treeScene = new BinaryTreeScene(font);
	linkedListScene = new LinkedListScene(font);
	
	//Set the starting scene to the main menu
	ChangeScene(menuScene);

	return true;
}

/// <summary>
/// Called when the application shuts down.
/// De-allocates memory.
/// </summary>
void CentipedeGameApp::shutdown()
{
	delete renderer;
	delete font;
	
	delete shipTexture;
	delete bulletTexture;

	delete gameScene;
	delete menuScene;
	delete listScene;
	delete treeScene;
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
void CentipedeGameApp::update(float deltaTime) 
{
	//Get Input Instance
	Input* input = Input::getInstance();

	//Update the scene if it isn't a nullptr
	if (currentScene != nullptr)
		currentScene->Update(deltaTime, input);

	//Exit the application
	if (input->isKeyDown(INPUT_KEY_ESCAPE))
		quit();
}

/// <summary>
/// Draws graphics to the screen.
/// </summary>
void CentipedeGameApp::draw() 
{
	//Clear the screen
	clearScreen();

	//Begin drawing sprites
	renderer->begin();

	//Draw the current scene if it isn't a nullptr
	if (currentScene != nullptr)
		currentScene->Draw(renderer);

	//Done drawing sprites
	renderer->end();
}

/// <summary>
/// Changes the scene, calling the appropriate functions on the old/new scene.
/// </summary>
/// <param name="newScene"></param>
void CentipedeGameApp::ChangeScene(Scene* newScene)
{
	//If we're given a nullptr then return
	if (newScene == nullptr)
		return;

	//Close the current scene if it exists
	if (currentScene != nullptr)
		currentScene->OnClose();

	//Set the new current scene
	currentScene = newScene;

	//Start the new current scene
	currentScene->OnStart();
}
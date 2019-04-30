#include "CentipedeGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "GameScene.h"
#include "ListScene.h"
#include "MenuScene.h"
#include "BinaryTreeScene.h"
#include "LinkedListScene.h"
#include "StackScene.h"
#include "DequeueScene.h"
#include "HashScene.h"
#include "QuadTreeScene.h"
#include "HeapScene.h"

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
	//Set the window size
	setWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	//Create the Renderer
	renderer = new Renderer2D();

	//Load the font(s)
	font = new Font("../bin/font/consolas.ttf", 30);

	//Load the texture(s)
	shipTexture = new Texture("../bin/textures/ship.png");
	bulletTexture = new Texture("../bin/textures/bullet.png");
	shroomTexture = new Texture("../bin/textures/mushroom.png");
	segmentTexture = new Texture("../bin/textures/segment.png");
	headTexture = new Texture("../bin/textures/head.png");
	tailTexture = new Texture("../bin/textures/tail.png");

	//Load the scenes(s)
	currentScene = nullptr;
	gameScene = new GameScene();
	menuScene = new MenuScene();
	listScene = new ListScene();
	treeScene = new BinaryTreeScene();
	linkedListScene = new LinkedListScene();
	stackScene = new StackScene();
	dequeueScene = new DequeueScene();
	hashScene = new HashScene();
	quadScene = new QuadScene();
	heapScene = new HeapScene();
	
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
	delete linkedListScene;
	delete stackScene;
	delete hashScene;
	delete quadScene;
	delete heapScene;
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

	//Check if ESCAPE was pressed
	if (input->wasKeyPressed(INPUT_KEY_ESCAPE))
	{
		//If we are on the main menu, then quit the app
		if (currentScene == menuScene)
			quit();
		//Otherwise return to the main menu
		else
			ChangeScene(menuScene);
	}
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

/// <summary>
/// Get a random integer between a min and max.
/// </summary>
/// <param name="min">Minimum value.</param>
/// <param name="max">Maximum value.</param>
/// <returns>Random number between min & max.</returns>
int CentipedeGameApp::RandomRange(int min, int max) const
{
	return (int)(rand() * (float)(max - min) / RAND_MAX + min + 0.5f);
}
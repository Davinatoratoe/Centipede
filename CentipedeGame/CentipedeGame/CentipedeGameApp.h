/*
	File: CentipedeGameApp.h
	Contains: CentipedeGameApp
*/

#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Scene.h"
#include <string>

using namespace aie;
using namespace std;

/// <summary>
/// The CentipedeGameApp is what runs the application.
/// </summary>
class CentipedeGameApp : public Application 
{
public:
	const unsigned int DEFAULT_WINDOW_WIDTH = 720;	//The default window width
	const unsigned int DEFAULT_WINDOW_HEIGHT = 900;	//The default window height
	
	//Set whether the build is DEBUG or RELEASE
	//https://stackoverflow.com/questions/2249282/c-c-portable-way-to-detect-debug-release
#ifdef NDEBUG
	const bool DEBUG = false;
#else
	const bool DEBUG = true;
#endif

	static CentipedeGameApp* instance;	//Static pointer to the one instance of this class	
	
	Renderer2D*	renderer;	//Pointer to the renderer used for displaying graphics

	Font* font;				//Pointer to the default font

	Texture* shipTexture;	//Pointer to the ship texture
	Texture* bulletTexture;	//Pointer to the bullet texture
	Texture* shroomTexture; //Pointer to the mushroom texture
	Texture* segmentTexture;//Pointer to the centipede segment texture
	Texture* headTexture;	//Pointer to the centipede head texture
	Texture* tailTexture;	//Pointer to the centipede tail texture

	//The currently active scene
	Scene* currentScene;

	//Pointers to the different scenes available
	Scene* gameScene;
	Scene* menuScene;
	Scene* listScene;
	Scene* treeScene;
	Scene* linkedListScene;
	Scene* stackScene;
	Scene* dequeueScene;
	Scene* hashScene;
	Scene* quadScene;
	Scene* heapScene;
	Scene* simonScene;

	CentipedeGameApp();				//Default constructor
	virtual ~CentipedeGameApp();	//Deconstructor

	virtual bool startup();			//Called when the game first starts up
	virtual void shutdown();		//Called when the game shuts down

	virtual void update(float deltaTime);	//Called once per frame
	virtual void draw();		//Draw the application

	//Get a resource
	Texture* GetTexture(string resourceName);
	Font* GetFont(string resourceName, unsigned short fontHeight);

	//Change the active scene
	void ChangeScene(Scene* newScene);	

	//Choose a random number between min and max
	int RandomRange(int min, int max) const;
};
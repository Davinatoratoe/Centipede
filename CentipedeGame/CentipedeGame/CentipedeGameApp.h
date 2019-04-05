/*
	File: CentipedeGameApp.h
	Contains: CentipedeGameApp
*/

#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Scene.h"

using namespace aie;

/// <summary>
/// The CentipedeGameApp is what runs the application.
/// </summary>
class CentipedeGameApp : public Application 
{
public:
	static CentipedeGameApp* instance;	//Static pointer to the one instance of this class	
	
	Renderer2D*	renderer;	//Pointer to the renderer used for displaying graphics

	Font* font;				//Pointer to the default font

	Texture* shipTexture;	//Pointer to the ship texture
	Texture* bulletTexture;	//Pointer to the bullet texture
	Texture* segmentTexture;//Pointer to the centipede segment texture
	Texture* headTexture;
	Texture* tailTexture;

	Scene* currentScene;	//Pointers to the different scenes in the application
	Scene* gameScene;
	Scene* menuScene;
	Scene* listScene;
	Scene* treeScene;
	Scene* linkedListScene;
	Scene* stackScene;
	Scene* dequeueScene;
	Scene* hashScene;

	CentipedeGameApp();				//Default constructor
	virtual ~CentipedeGameApp();	//Deconstructor

	virtual bool startup();			//Called when the game first starts up
	virtual void shutdown();		//Called when the game shuts down

	virtual void update(float deltaTime);	//Called once per frame
	virtual void draw();		//Draw the application

	void ChangeScene(Scene* newScene);	//Change the active scene
};
/*
	File: Scene.h
	Contains: Scene
*/

#pragma once
#include "Input.h"
#include "Renderer2D.h"

using namespace aie;

class CentipedeGameApp;

/// <summary>
/// Scene is a virtual class that should be inherited from.
/// It represents a state in the application and can be used for menus, games, loading screens, etc.
/// </summary>
class Scene
{
public:
	CentipedeGameApp* app;		//Pointer to the app
	bool sceneStarted;			//Did the scene just start?

	Scene();	//Default constructor
	~Scene();	//Deconstructor

	virtual void OnStart() = 0;									//Called when the scene starts
	virtual void OnClose() = 0;									//Called when the scene closes
	virtual void Update(float deltaTime, Input* input) = 0;		//Called once per frame to update the scene
	virtual void Draw(Renderer2D* renderer) = 0;				//Called to draw the scene

protected:
	void CreateGUI(const char *name, float width = 280);
};
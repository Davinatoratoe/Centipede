/*
	File: MenuScene.h
	Contains: MenuScene
*/

#pragma once
#include "Scene.h"

/// <summary>
/// The MenuScene is a scene for the main menu.
/// Allows loading the main game and container tests.
/// </summary>
class MenuScene : public Scene
{
public:
	MenuScene();	//Overloaded constructor
	~MenuScene();	//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Called to draw the graphics

private:
	float counter;					//Counter used as input for the sin wave for changing colours
	bool r;							//Whether to fade the red component
	bool g;							//Whether to fade the green component
	bool b;							//Whether to fade the blue component
	unsigned int colourCounter;		//Keep track of which colour is being faded to
};


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
};


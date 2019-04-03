/*
	File: StackScene.h
	Contains: StackScene
*/

#pragma once
#include "Scene.h"
#include "Stack.h"

/// <summary>
/// Stack Scene is used to test and manipulate a Stack container graphically.
/// </summary>
class StackScene : public Scene
{
private:
	Stack<int> stack;	//The Linked List to manipulate
	int value;				//The value to manipulate
	Font* font;				//The font to use

public:
	StackScene(Font* _font);	//Overloaded constructor
	~StackScene();				//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the graphics of the scene
};


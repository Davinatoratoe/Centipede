/*
	File: DequeueScene.h
	Contains: DequeueScene
*/

#pragma once
#include "Scene.h"
#include "Dequeue.h"

/// <summary>
/// The Dequeue Scene allows manipulating and displaying a Dequeue container.
/// </summary>
class DequeueScene : public Scene
{
private:
	Dequeue<int> dequeue;	//The Linked List to manipulate
	int value;				//The value to manipulate
	Font* font;				//The font to use

public:
	DequeueScene(Font* _font);	//Overloaded constructor
	~DequeueScene();			//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the graphics of the scene
};


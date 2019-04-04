/*
	File: ListScene.h
	Contains: ListScene
*/

#pragma once
#include "Scene.h"
#include "DynamicList.h"

/// <summary>
/// The list scene allows testing the Dynamic List
/// </summary>
class ListScene : public Scene
{
private:
	List<int> list;		//The list to alter
	int value;			//The value to alter

public:
	ListScene();		//Overloaded constructor
	~ListScene();		//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the graphics
};


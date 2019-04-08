/*
	File: QuadTreeScene.h
	Contains: QuadScene
*/

#pragma once
#include "Scene.h"
#include "QuadTree.h"
#include "DynamicList.h"

/// <summary>
/// The list scene allows testing the Quad Tree
/// </summary>
class QuadScene : public Scene
{
private:
	QuadTree quadTree;			//The quad tree
	Texture* shipTexture;		//Pointer to the ship texture
	Texture* mushroomTexture;	//Pointer to the mushroom texture
	Texture* selectedTexture;	//Pointer to the selected texture
	List<Sprite*> sprites;		//List of sprites for testing the quad tree

public:
	QuadScene();		//Overloaded constructor
	~QuadScene();		//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the graphics
};

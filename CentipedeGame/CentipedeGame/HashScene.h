/*
	File: HashScene.h
	Contains: HashScene
*/

#pragma once
#include <iostream>
#include "Scene.h"

using namespace std;

/// <summary>
/// Scene to use hashing including using a hash table to load textures.
/// </summary>
class HashScene : public Scene
{
private:
	map<unsigned int, Texture*>* loadedTextures;	//Hash map of loaded textures
	unsigned int hashToDisplay;						//Hash number to insert into hash table
	Texture* textureToDisplay;						//Texture loaded from hash table
	unsigned char* shipTextureFileName;				//File name for the ship texture
	unsigned int shipTextureFileNameLength;			//Length of the file name of the ship texture

public:
	HashScene();		//Overloaded constructor
	~HashScene();		//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	Texture* GetTexture(unsigned int ID);

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the graphics
};


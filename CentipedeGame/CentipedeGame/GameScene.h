/*
	File: GameScene.h
	Contains: GameScene
*/

#pragma once
#include "Scene.h"
#include "Player.h"

/// <summary>
/// The scene responsible for the gameplay.
/// </summary>
class GameScene : public Scene
{
public:
	Player* player;		//Pointer to the player

	GameScene(Texture* playerTexture);	//Overloaded constructor
	~GameScene();						//Deconstructor

	void OnStart() override;
	void OnClose() override;
	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;
};


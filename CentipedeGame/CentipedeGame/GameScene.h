/*
	File: GameScene.h
	Contains: GameScene
*/

#pragma once
#include "Scene.h"
#include "Player.h"
#include "Centipede.h"
#include "DynamicList.h"
#include "QuadTree.h"

/// <summary>
/// The scene responsible for the gameplay.
/// </summary>
class GameScene : public Scene
{
public:
	Player* player;								//Pointer to the player
	List<Sprite*>* mushrooms;					//Pointer to the mushrooms
	CentipedeController* centipedeController;	//Pointer to the centipede controller
	bool gameOver;		//True if the player lost

	GameScene();	//Overloaded constructor
	~GameScene();	//Deconstructor

	void OnStart() override;
	void OnClose() override;

	void SpawnMushroom(float x, float y);

	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;
};


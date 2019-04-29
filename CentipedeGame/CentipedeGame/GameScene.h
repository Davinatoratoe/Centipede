/*
	File: GameScene.h
	Contains: GameScene
*/

#pragma once
#include "Scene.h"
#include "Player.h"
#include "Centipede.h"
#include "DynamicList.h"

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
	unsigned int score;	//The score
	unsigned int wave;	//The wave, increases when all centipedes are defeated

	unsigned int CENTIPEDE_INITIAL_LENGTH = 20;	//The initial length of the first centipede

	GameScene();	//Overloaded constructor
	~GameScene();	//Deconstructor

	//Called when the game starts
	void OnStart() override;

	//Called when the game ends
	void OnClose() override;

	//Spawn a mushroom in the game at a given position
	void SpawnMushroom(float x, float y);

	//Update the game logic
	void Update(float deltaTime, Input* input) override;

	//Draw the game
	void Draw(Renderer2D* renderer) override;
};


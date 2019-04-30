/*
	File: GameScene.h
	Contains: GameScene
*/

#pragma once
#include "Scene.h"
#include "Player.h"
#include "Centipede.h"
#include "DynamicList.h"
#include "Word.h"

/// <summary>
/// The scene responsible for the gameplay.
/// </summary>
class GameScene : public Scene
{
private:
	unsigned int score;	//The score
	unsigned int displayScore;	//The score to be displayed (not the same as score)
	unsigned int addDisplayScore;	//The speed to add to the display score (larger for larger scores)
	unsigned int wave;	//The wave, increases when all centipedes are defeated
	bool gameOver;		//True if the player lost
	Word* gameOverTitle;	//Word displaying that the game was lost

public:
	Player* player;								//Pointer to the player
	List<Sprite*>* mushrooms;					//Pointer to the mushrooms
	CentipedeController* centipedeController;	//Pointer to the centipede controller
	
	const unsigned int CENTIPEDE_INITIAL_LENGTH = 20;	//The initial length of the first centipede
	const unsigned int SCORE_SEGMENT_KILLED = 50;		//The points gained when a segment is killed
	const unsigned int SCORE_CENTIPEDE_KILLED = 200;	//The points gained when a centipede is killed
	const unsigned int SCORE_WAVE_COMPLETE = 1000;		//The points gained when the first wave is completed (incremental)
	const float MUSHROOM_ROTATE_SPEED = 0.3F;			//The speed that the mushrooms rotate

	GameScene();	//Overloaded constructor
	~GameScene();	//Deconstructor

	//Called when the game starts
	void OnStart() override;

	//Called when the game ends
	void OnClose() override;

	//Generate a field of mushrooms
	void GenerateMushrooms(unsigned int amount);

	//Spawn a mushroom in the game at a given position
	void SpawnMushroom(float x, float y);

	//Add score to the scoreboard
	void AddScore(unsigned int amount);

	//Update the game logic
	void Update(float deltaTime, Input* input) override;

	//Draw the game
	void Draw(Renderer2D* renderer) override;
};


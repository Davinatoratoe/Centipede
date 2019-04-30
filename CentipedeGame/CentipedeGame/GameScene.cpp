#include "GameScene.h"
#include "CentipedeGameApp.h"
#include "imgui.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
GameScene::GameScene()
{
	player = new Player();
	mushrooms = new List<Sprite*>(50);
	centipedeController = new CentipedeController();
}

/// <summary>
/// Deconstructor.
/// </summary>
GameScene::~GameScene()
{
	delete player;
	delete mushrooms;
	delete centipedeController;
}

/// <summary>
/// Called when the scene starts.
/// </summary>
void GameScene::OnStart()
{
	//Input a seed for the random number generator
	srand((unsigned int)app->getTime());

	//Set the window size
	app->setWindowSize(app->DEFAULT_WINDOW_WIDTH, app->DEFAULT_WINDOW_HEIGHT);

	//Set values to initial state
	gameOver = false;
	score = 0;
	wave = 0;

	//Set the starting position of the player ship
	player->position.x = 100;
	player->position.y = 70;

	//Create the centipede at the top of the screen with an initial length of 20
	centipedeController->Reset((float)app->getWindowWidth() / 2, (float)app->getWindowHeight() - 50, CENTIPEDE_INITIAL_LENGTH);

	//Generate random mushroom placements
	const int MAX_MUSHROOMS = 25;	//The number of mushrooms to generate
	int numberOfMushrooms = 0;		//The number of mushrooms that have been generated

	//While the number of mushrooms that have been generated does not exceed the max number, spawn mushrooms
	while (numberOfMushrooms < MAX_MUSHROOMS)
	{
		SpawnMushroom(
			(float)app->RandomRange(50, app->getWindowWidth() - 50),	//Choose a random x-position
			(float)app->RandomRange(200, app->getWindowHeight() - 50)	//Choose a random y-position
		);
		++numberOfMushrooms;	//Increment the number of mushrooms generated
	}
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void GameScene::OnClose()
{
	player->bullets->Clear();
	(*mushrooms).Clear();
}

/// <summary>
/// Spawn a mushroom at the specified position.
/// </summary>
/// <param name="x">The x-position of the mushroom.</param>
/// <param name="y">The y-position of the mushroom.</param>
void GameScene::SpawnMushroom(float x, float y)
{
	//Create the mushroom
	Sprite* mushroom = new Sprite(app->shroomTexture, x, y);

	//Give the mushroom a random rotation
	mushroom->rotation = (float)rand();

	//Spawn the mushroom
	mushrooms->Push(mushroom);
}

/// <summary>
/// Called once per frame. Updates the game logic.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
/// <param name="input">Pointer to the input handler.</param>
void GameScene::Update(float deltaTime, Input* input) 
{
	//If the game is running
	if (!gameOver)
	{
		//Check that the window hasn't been resized, and if so, resize it back
		if (app->getWindowWidth() != app->DEFAULT_WINDOW_WIDTH || app->getWindowHeight() != app->DEFAULT_WINDOW_HEIGHT)
			app->setWindowSize(app->DEFAULT_WINDOW_WIDTH, app->DEFAULT_WINDOW_HEIGHT);

		//Update the player
		player->Update(deltaTime, input);

		//Update the mushrooms
		for (unsigned int i = 0; i < (*mushrooms).Size(); ++i)
		{
			(*((*mushrooms)[i])).Update(deltaTime, input);

			//Spin the mushrooms because now they're asteroids
			(*((*mushrooms)[i])).rotation += 0.2F * deltaTime;
		}

		//Update the centipedes
		centipedeController->Update(deltaTime, input);

		//If the centipede was destroyed, spawn another
		if (centipedeController->centipedes->Size() == 0)
		{
			centipedeController->Reset((float)app->getWindowWidth() / 2, (float)app->getWindowHeight() - 50, 20 + (wave * 2));
			++wave;
			score += SCORE_WAVE_COMPLETE * wave;
		}

		//Check through the centipede's heads to see if they are below the player
		for (unsigned int i = 0; i < centipedeController->centipedes->Size(); ++i)
		{
			//Pointer to the centipede
			Centipede* centipede = (*centipedeController->centipedes)[i];

			//Check if the head of the centipede has reached the player, and if so - end the game
			if (centipede->segments->First()->position.y < player->position.y + player->texture->getHeight())
			{
				gameOver = true;
				return;
			}
		}
	}
	//If the game was lost
	else
	{
		CreateGUI("Game Over");

		//Button to play the game again
		if (Button("Play again", ImVec2(150, 0)))
			app->ChangeScene(app->gameScene);

		//Button to return to the main menu
		if (Button("Menu", ImVec2(150, 0)))
			app->ChangeScene(app->menuScene);

		End();
	}
}

/// <summary>
/// Draw graphics.
/// </summary>
/// <param name="renderer">Pointer to the renderer.</param>
void GameScene::Draw(Renderer2D* renderer)
{
	//Draw the player
	player->Draw(renderer);

	//Draw the mushrooms
	for (unsigned int i = 0; i < mushrooms->Size(); ++i)
		(*mushrooms)[i]->Draw(renderer);

	//Draw the centipedes
	centipedeController->Draw(renderer);

	//Draw final score and game over text
	if (gameOver)
	{
		renderer->drawText(app->font, "Game over!", 20, 850);
		renderer->drawText(app->font, ("Final score: " + to_string(score)).c_str(), 20, 800);
		renderer->drawText(app->font, ("Wave: " + to_string(wave + 1)).c_str(), 20, 750);
	}
	else
	{
		//Draw details
		renderer->drawText(app->font, ("Score: " + to_string(score)).c_str(), 20, 850);
		renderer->drawText(app->font, ("Wave: " + to_string(wave + 1)).c_str(), 20, 800);
	}
}
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
	gameOverTitle = new Word("Game Over!", 11, app->font, 40, 20, 850);
}

/// <summary>
/// Deconstructor.
/// </summary>
GameScene::~GameScene()
{
	delete player;
	delete mushrooms;
	delete centipedeController;
	delete gameOverTitle;
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
	displayScore = 0;
	addDisplayScore = 1;
	wave = 0;
	cheatWindow = false;
	cheatValue = 0;

	//Set the starting position of the player ship
	player->position.x = 100;
	player->position.y = 70;

	//Create the centipede at the top of the screen with an initial length of 20
	SpawnCentipede(CENTIPEDE_INITIAL_LENGTH);

	//Generate mushrooms
	GenerateMushrooms(25);
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
/// Spawn a centipede at the top of the screen.
/// </summary>
/// <param name="length">The length of the centipede.</param>
void GameScene::SpawnCentipede(unsigned int length)
{
	centipedeController->Reset((float)app->getWindowWidth() / 2, (float)app->getWindowHeight() - 50, length);
}

/// <summary>
/// Generate mushrooms on the field.
/// </summary>
/// <param name="amount">The number of mushrooms to generate.</param>
void GameScene::GenerateMushrooms(unsigned int amount)
{
	//Generate random mushroom placements
	unsigned int numberOfMushrooms = 0;		//The number of mushrooms that have been generated

	//While the number of mushrooms that have been generated does not exceed the max number, spawn mushrooms
	while (numberOfMushrooms < amount)
	{
		SpawnMushroom(
			(float)app->RandomRange(50, app->getWindowWidth() - 50),	//Choose a random x-position
			(float)app->RandomRange(200, app->getWindowHeight() - 50)	//Choose a random y-position
		);
		++numberOfMushrooms;	//Increment the number of mushrooms generated
	}
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
/// Add points to the score.
/// </summary>
/// <param name="amount">The points to add.</param>
void GameScene::AddScore(unsigned int amount)
{
	//Add the amount to the real score
	score += amount;

	//If the difference between the real score and the displayed score is large,
	//Then increase the displayed score faster
	if (score - displayScore > 1000)
		addDisplayScore = 100;
	else if (score - displayScore > 100)
		addDisplayScore = 5;
	else
		addDisplayScore = 1;
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
		//Check whether to activate the cheat window
		if (input->wasKeyPressed(INPUT_KEY_D))
			cheatWindow = !cheatWindow;

		//Cheat window
		if (cheatWindow)
		{
			CreateGUI("Cheats");

			//Get an input value
			InputInt("Value: ", &cheatValue);

			//Create a new centipede with a certain length
			if (Button("Set length", ImVec2(150, 0)))
				SpawnCentipede(cheatValue);

			//Add points
			else if (Button("Add points", ImVec2(150, 0)))
				AddScore(cheatValue);

			//Change the wave
			else if (Button("Wave #", ImVec2(150, 0)))
				wave = cheatValue;

			//Beat wave
			else if (Button("Beat wave", ImVec2(150, 0)))
				centipedeController->centipedes->Clear();

			End();
		}

		//Check if the displayed score isn't the same as the real score, and increase if so
		if (displayScore < score)
			displayScore += addDisplayScore;
		else
			displayScore = score;

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
			(*((*mushrooms)[i])).rotation += MUSHROOM_ROTATE_SPEED * deltaTime;
		}

		//Update the centipedes
		centipedeController->Update(deltaTime, input);

		//If the centipede was destroyed, spawn another
		if (centipedeController->centipedes->Size() == 0)
		{
			//Create a new centipede
			SpawnCentipede(CENTIPEDE_INITIAL_LENGTH + (wave * 3));

			//Generate more mushrooms
			GenerateMushrooms(mushrooms->Size() / 3);

			//Clear the player's bullets
			player->bullets->Clear();

			//Increment the wave
			++wave;

			//Add to the score
			AddScore(SCORE_WAVE_COMPLETE * wave);
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
		//Update the game over title so that it bobs
		gameOverTitle->Update(deltaTime);

		//Create the menu GUI
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
		//renderer->drawText(app->font, "Game over!", 20, 850);
		gameOverTitle->Draw(renderer);
		renderer->drawText(app->font, ("Final score: " + to_string(score)).c_str(), 20, 800);
		renderer->drawText(app->font, ("Wave: " + to_string(wave + 1)).c_str(), 20, 750);
	}
	else
	{
		//Draw details
		renderer->drawText(app->font, ("Score: " + to_string(displayScore)).c_str(), 20, 850);
		renderer->drawText(app->font, ("Wave: " + to_string(wave + 1)).c_str(), 20, 800);
	}
}
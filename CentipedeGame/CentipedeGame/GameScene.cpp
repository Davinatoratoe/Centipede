#include "GameScene.h"
#include "CentipedeGameApp.h"
#include "imgui.h"

using namespace ImGui;

GameScene::GameScene()
{
	player = new Player();
	mushrooms = new List<Sprite*>(150);
	centipedeController = new CentipedeController();
}

GameScene::~GameScene()
{
	delete player;
	delete mushrooms;
	delete centipedeController;
}

void GameScene::OnStart()
{
	gameOver = false;
	player->position.x = 100;
	player->position.y = 70;
	centipedeController->Reset(app->getWindowWidth() / 2, app->getWindowHeight() - 50, 20);

	//Generate random mushroom placements
	const int MAX_MUSHROOMS = 100;
	int numberOfMushrooms = 0;
	while (numberOfMushrooms < MAX_MUSHROOMS)
	{
		SpawnMushroom(
			app->RandomRange(50, app->getWindowWidth() - 50),
			app->RandomRange(200, app->getWindowHeight() - 50)
		);
		++numberOfMushrooms;
	}
}

void GameScene::OnClose()
{
	player->bullets->Clear();
	(*mushrooms).Clear();
}

void GameScene::SpawnMushroom(float x, float y)
{
	mushrooms->Push(new Sprite(app->shroomTexture, x, y));
}

void GameScene::Update(float deltaTime, Input* input) 
{
	if (!gameOver)
	{
		//Update the player
		player->Update(deltaTime, input);

		//Update the mushrooms
		for (unsigned int i = 0; i < (*mushrooms).Size(); ++i)
			(*((*mushrooms)[i])).Update(deltaTime, input);

		//Update the centipedes
		centipedeController->Update(deltaTime, input);

		//TESTING
		if (input->wasMouseButtonPressed(0))
			SpawnMushroom(input->getMouseX(), input->getMouseY());
	}
	else
	{
		if (Button("Play again", ImVec2(50, 0)))
			app->ChangeScene(app->gameScene);

		if (Button("Menu", ImVec2(50, 0)))
			app->ChangeScene(app->menuScene);
	}
}

void GameScene::Draw(Renderer2D* renderer)
{
	//Draw the player
	player->Draw(renderer);

	//Draw the mushrooms
	for (unsigned int i = 0; i < (*mushrooms).Size(); ++i)
		(*((*mushrooms)[i])).Draw(renderer);

	//Draw the centipedes
	centipedeController->Draw(renderer);
}

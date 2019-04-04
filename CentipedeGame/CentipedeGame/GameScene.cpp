#include "GameScene.h"
#include "CentipedeGameApp.h"

GameScene::GameScene()
{
	player = new Player();
	mushrooms = new List<Sprite*>(20);
}

GameScene::~GameScene()
{
	delete player;
	delete mushrooms;
}

void GameScene::OnStart()
{
	player->position.x = 100;
	player->position.y = 70;	
}

void GameScene::OnClose()
{
	player->bullets->Clear();
}

void GameScene::SpawnMushroom(float x, float y)
{
	(*mushrooms).Push(new Sprite(app->bulletTexture, x, y));
}

void GameScene::Update(float deltaTime, Input* input) 
{
	player->Update(deltaTime, input);

	for (unsigned int i = 0; i < (*mushrooms).Size(); ++i)
		(*((*mushrooms)[i])).Update(deltaTime, input);
}

void GameScene::Draw(Renderer2D* renderer)
{
	player->Draw(renderer);

	for (unsigned int i = 0; i < (*mushrooms).Size(); ++i)
		(*((*mushrooms)[i])).Draw(renderer);
}

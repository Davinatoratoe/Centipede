#include "GameScene.h"
#include "CentipedeGameApp.h"

GameScene::GameScene(Texture* playerTexture, Texture* bulletTexture)
{
	player = new Player(playerTexture, bulletTexture);
}

GameScene::~GameScene()
{
	delete player;
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

void GameScene::Update(float deltaTime, Input* input) 
{
	player->Update(deltaTime, input);
}

void GameScene::Draw(Renderer2D* renderer)
{
	player->Draw(renderer);
}

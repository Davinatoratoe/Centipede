#include "GameScene.h"

GameScene::GameScene(Texture* playerTexture)
{
	player = new Player(playerTexture);
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

}

void GameScene::Update(float deltaTime, Input* input) 
{
	player->Update(deltaTime, input);
}

void GameScene::Draw(Renderer2D* renderer)
{
	player->Draw(renderer);
}

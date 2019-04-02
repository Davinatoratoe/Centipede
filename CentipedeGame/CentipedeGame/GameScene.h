#pragma once
#include "Scene.h"
#include "Player.h"

class GameScene : public Scene
{
public:
	Player* player;

	GameScene(Texture* playerTexture);
	~GameScene();

	void OnStart() override;
	void OnClose() override;
	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;
};


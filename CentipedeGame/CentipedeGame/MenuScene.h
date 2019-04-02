#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	Font* font;

	MenuScene(Font* _font);
	~MenuScene();

	void OnStart() override;
	void OnClose() override;

	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;
};


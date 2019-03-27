#pragma once
#include "Sprite.h"
#include "Input.h"

class Player : Sprite
{
public:
	Player(Texture* _texture, float x, float y);
	~Player();

	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;

protected:
	const float MAX_SPEED = 80;
};


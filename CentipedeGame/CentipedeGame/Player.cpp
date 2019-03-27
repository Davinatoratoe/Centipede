#include "Player.h"
#include "CentipedeGameApp.h"

Player::Player(Texture* _texture, float x, float y)
{
	position.x = x;
	position.y = y;
	texture = _texture;
}

Player::~Player()
{
}

void Player::Update(float deltaTime, Input* input)
{
	Sprite::Update(deltaTime, input);

	if (input->isKeyDown(INPUT_KEY_LEFT))
	{
		position.x -= MAX_SPEED * deltaTime;
		if (position.x < Radius())
			position.x = Radius();
	}
	else if (input->isKeyDown(INPUT_KEY_RIGHT))
	{
		position.x += MAX_SPEED * deltaTime;
		if (position.x > app->getWindowWidth() - Radius())
			position.x = app->getWindowWidth() - Radius();
	}
}

void Player::Draw(Renderer2D* renderer)
{
	Sprite::Draw(renderer);
}

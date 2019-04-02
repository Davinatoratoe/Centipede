#pragma once
#include "Sprite.h"
#include "Input.h"

class Player : public Sprite
{
public:
	Player(Texture* _texture);		//Default constructor
	~Player();						//Deconstructor

	//Update the player and move according to inputs
	void Update(float deltaTime, Input* input) override;

	//Draw the player ship to the screen
	void Draw(Renderer2D* renderer) override;

protected:
	const float MAX_SPEED = 80;		//The movement speed of the player
};


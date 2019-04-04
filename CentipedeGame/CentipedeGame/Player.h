#pragma once
#include "Sprite.h"
#include "Input.h"
#include "DynamicList.h"

class Player : public Sprite
{
public:
	List<Sprite*>* bullets;			//Pointer to a list of pointers to sprites - the bullets

	Player();		//Default constructor
	~Player();						//Deconstructor

	//Update the player and move according to inputs
	void Update(float deltaTime, Input* input) override;

	void Shoot();

	//Draw the player ship to the screen
	void Draw(Renderer2D* renderer) override;

private:
	const float MAX_SPEED = 350;		//The movement speed of the player
	const float BULLET_SPEED = 650;		//The movement speed of bullets
	const float BULLET_COOLDOWN = 0.3f;	//The cooldown between firing bullets (in seconds)
	float bulletCooldown;				//The timer used to track whether the player can shoot again (in seconds)
	Texture* bulletTexture;				//Pointer to the texture for the bullets
};


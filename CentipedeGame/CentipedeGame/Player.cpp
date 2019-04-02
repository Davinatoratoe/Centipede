#include "Player.h"
#include "CentipedeGameApp.h"

/// <summary>
/// Default constructor.
/// </summary>
/// <param name="_texture">The texture that the player should use.</param>
/// <param name="x">Initial starting position on the x-axis.</param>
/// <param name="y">Initial starting position on the y-axis.</param>
Player::Player(Texture* _texture)
{
	texture = _texture;
}

/// <summary>
/// Deconstructor.
/// </summary>
Player::~Player()
{
}

/// <summary>
/// Update loop for the player.
/// Handles input - moving the ship and firing bullets.
/// </summary>
/// <param name="deltaTime">The time that has passed since last update.</param>
/// <param name="input">Pointer to the input handler.</param>
void Player::Update(float deltaTime, Input* input)
{
	//Call the base update so it can perform its operations - if any
	Sprite::Update(deltaTime, input);

	//Check if the LEFT or RIGHT key is being pressed and move the ship accordingly
	//Stop the ship from moving off the edge of the screen
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

/// <summary>
/// Draw the player ship.
/// </summary>
/// <param name="renderer">A pointer to the renderer to display graphics.</param>
void Player::Draw(Renderer2D* renderer)
{
	Sprite::Draw(renderer);		//Call the base class to handle drawing the ship
}

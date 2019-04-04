#include "Player.h"
#include "CentipedeGameApp.h"

/// <summary>
/// Default constructor.
/// </summary>
/// <param name="_texture">The texture that the player should use.</param>
/// <param name="x">Initial starting position on the x-axis.</param>
/// <param name="y">Initial starting position on the y-axis.</param>
Player::Player()
{
	texture = app->shipTexture;
	bulletTexture = app->bulletTexture;
	bullets = new List<Sprite*>;
	bulletCooldown = BULLET_COOLDOWN / 2;
}

/// <summary>
/// Deconstructor.
/// </summary>
Player::~Player()
{
	delete bullets;
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

	//If there is a cooldown on shooting bullets, then wait
	if (bulletCooldown > 0)
		bulletCooldown -= deltaTime;
	//If the cooldown has expired and the shoot key is pressed, shoot a bullet
	else if (input->isKeyDown(INPUT_KEY_SPACE))
		Shoot();

	//Iterate through the bullets and update them appropriately
	//Instead of making a new bullet class that handles the update, we will just do it here
	for (unsigned int i = 0; i < bullets->Size(); ++i)
	{
		Sprite& bullet = (*((*bullets)[i]));

		//Call the default update on the bullet sprite class
		bullet.Update(deltaTime, input);

		//Move the bullet up the screen
		bullet.position.y += BULLET_SPEED * deltaTime;

		//Remove the bullet if it is over the top of the screen
		if (bullet.position.y > app->getWindowHeight() + 50)
		{
			(*bullets).Remove(i);
			--i;
		}
	}
}

/// <summary>
/// Shoot a bullet from the ship.
/// </summary>
void Player::Shoot()
{
	//Add a new bullet to the bullets dynamic list
	bullets->Push(new Sprite(bulletTexture, position.x, position.y + Radius()));

	//Reset the bullet cool down
	bulletCooldown = BULLET_COOLDOWN;
}

/// <summary>
/// Draw the player ship.
/// </summary>
/// <param name="renderer">A pointer to the renderer to display graphics.</param>
void Player::Draw(Renderer2D* renderer)
{
	Sprite::Draw(renderer);		//Call the base class to handle drawing the ship

	for (unsigned int i = 0; i < bullets->Size(); ++i)
		(*((*bullets)[i])).Draw(renderer);
}

#include "Sprite.h"
#include "CentipedeGameApp.h"

/// <summary>
/// Default constructor.
/// Sets the initial values and sets the app instance.
/// </summary>
Sprite::Sprite()
{
	texture = nullptr;
	app = CentipedeGameApp::instance;	//Static instance on the App class
}

/// <summary>
/// Deconstructor.
/// Will delete the texture from memory if it exists.
/// </summary>
Sprite::~Sprite()
{
	if (texture != nullptr)
		delete texture;
}

/// <summary>
/// Get the radius of the sprite using the texture dimensions.
/// </summary>
/// <returns>The radius of the sprite.</returns>
float Sprite::Radius() const
{
	if (texture == nullptr)
		return 0;
	return (float)((texture->getWidth() + texture->getHeight() / 2) / 2);
}

/// <summary>
/// Get the distance between this sprite and another sprite.
/// </summary>
/// <param name="other">The other sprite.</param>
/// <returns>The distance between this sprite and the other sprite.</returns>
float Sprite::Distance(const Sprite& other) const
{
	return sqrt(pow(other.position.x - position.x, 2) + pow(other.position.y - position.y, 2));
}

/// <summary>
/// Check if this sprite is colliding with another sprite.
/// Uses circle collision detection by comparing the distance between them and their radi.
/// </summary>
/// <param name="other">The other sprite.</param>
/// <returns>True, if the sprite's circle colliders overlap.</returns>
bool Sprite::CollidingWith(const Sprite& other) const
{
	if (texture == nullptr || other.texture == nullptr)
		return false;
	return Distance(other) < Radius() * other.Radius();
}

/// <summary>
/// Called once per frame to update the sprite logic and input handling.
/// </summary>
/// <param name="deltaTime">The time that has passed since the last update.</param>
/// <param name="input">Pointer to the input handler to allow checking user input.</param>
void Sprite::Update(float deltaTime, Input* input)
{

}

/// <summary>
/// Draw the sprite to the screen.
/// </summary>
/// <param name="renderer">A pointer to the renderer used to draw graphics to the screen.</param>
void Sprite::Draw(Renderer2D* renderer)
{
	if (texture == nullptr)
		return;

	renderer->drawSprite(texture, position.x, position.y);
}

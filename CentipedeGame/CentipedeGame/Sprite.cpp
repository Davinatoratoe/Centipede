#include "Sprite.h"
#include "CentipedeGameApp.h"
#include "DynamicList.h"
#include "Dequeue.h"

/// <summary>
/// Default constructor.
/// Sets the initial values and sets the app instance.
/// </summary>
Sprite::Sprite()
{
	texture = nullptr;
	position = Point2D();
	oldPosition = Point2D();
	rotation = 0;
	app = CentipedeGameApp::instance;	//Static instance on the App class
}

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_texture">The texture that the sprite will use.</param>
Sprite::Sprite(Texture* _texture)
{
	texture = _texture;
	position = Point2D();
	oldPosition = Point2D();
	rotation = 0;
	app = CentipedeGameApp::instance;
}

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_texture">The texture that the sprite will use.</param>
/// <param name="x">The initial x position of the sprite.</param>
/// <param name="y">The initial y position of the sprite.</param>
Sprite::Sprite(Texture* _texture, float x, float y)
{
	texture = _texture;
	position = Point2D(x, y);
	oldPosition = Point2D();
	rotation = 0;
	app = CentipedeGameApp::instance;
}

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="x">The initial x position of the sprite.</param>
/// <param name="y">The initial y position of the sprite.</param>
Sprite::Sprite(float x, float y)
{
	texture = nullptr;
	position = Point2D(x, y);
	oldPosition = Point2D();
	rotation = 0;
	app = CentipedeGameApp::instance;
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
/// Set the rotation using degrees.
/// </summary>
/// <param name="degrees">The degree value to set the rotation to.</param>
float Sprite::ToRadians(float degrees) const
{
	return (degrees * (3.14159265358979f / 180));
}

/// <summary>
/// Get the rotation as degrees.
/// </summary>
/// <returns>The rotation as degrees.</returns>
float Sprite::ToDegrees(float radians) const
{
	return (radians * (180 / 3.14159265358979f));
}

/// <summary>
/// Called once per frame to update the sprite logic and input handling.
/// </summary>
/// <param name="deltaTime">The time that has passed since the last update.</param>
/// <param name="input">Pointer to the input handler to allow checking user input.</param>
void Sprite::Update(float deltaTime, Input* input)
{
	oldPosition = position;
}

/// <summary>
/// Draw the sprite to the screen.
/// </summary>
/// <param name="renderer">A pointer to the renderer used to draw graphics to the screen.</param>
void Sprite::Draw(Renderer2D* renderer)
{
	if (texture == nullptr)
		return;

	renderer->drawSprite(texture, position.x, position.y, 0, 0, rotation, 0, 0.5f, 0.5f);
}

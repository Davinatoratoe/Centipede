#include "Centipede.h"
#include "CentipedeGameApp.h"

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="x">The initial x position of the segment.</param>
/// <param name="y">The initial y position of the segment.</param>
Segment::Segment(float x, float y, bool isHead, bool isTail)
{
	if (isHead)
		SetHead();
	else if (isTail)
		SetTail();
	else
		texture = app->segmentTexture;
	position.x = x;
	position.y = y;
}

/// <summary>
/// Deconstructor.
/// </summary>
Segment::~Segment()
{

}

/// <summary>
/// Set the texture of this segment to the head texture.
/// </summary>
void Segment::SetHead()
{
	texture = app->headTexture;
}

/// <summary>
/// Set the texture of this segment to the tail texture.
/// </summary>
void Segment::SetTail()
{
	texture = app->tailTexture;
}

/// <summary>
/// Rotate the segment to face the direction of motion.
/// </summary>
void Segment::RotateToFace()
{
	Point2D movement = position - oldPosition;
	//If moving down, face down
	if (movement.y < 0)
		rotation = ToRadians(270);
	//If moving right, face right
	else if (movement.x > 0)
		rotation = 0;
	//If moving left, face left
	else
		rotation = ToRadians(180);
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void Segment::Update(float deltaTime, Input* input)
{
	Sprite::Update(deltaTime, input);
}

/// <summary>
/// Draw the segment.
/// </summary>
/// <param name="renderer">A pointer to the renderer.</param>
void Segment::Draw(Renderer2D* renderer)
{
	Sprite::Draw(renderer);
}
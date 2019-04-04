#include "Centipede.h"
#include "CentipedeGameApp.h"

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="x">The initial x position of the segment.</param>
/// <param name="y">The initial y position of the segment.</param>
Segment::Segment(float x, float y)
{
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
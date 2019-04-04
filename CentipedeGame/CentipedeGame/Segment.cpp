#include "Centipede.h"
#include "CentipedeGameApp.h"

Segment::Segment(float x, float y)
{
	texture = app->segmentTexture;
	position.x = x;
	position.y = y;
}

Segment::~Segment()
{

}

void Segment::Update(float deltaTime, Input* input)
{
	Sprite::Update(deltaTime, input);
}

void Segment::Draw(Renderer2D* renderer)
{
	Sprite::Draw(renderer);
}
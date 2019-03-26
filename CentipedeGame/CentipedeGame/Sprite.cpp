#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	if (texture != nullptr)
		delete texture;
}

int Sprite::Radius() const
{
	if (texture == nullptr)
		return 0;
	return texture->getWidth() + texture->getHeight() / 4;
}

int Sprite::Distance(const Sprite& other) const
{
	return sqrt(pow(other.position.x - position.x, 2) + pow(other.position.y - position.y, 2));
}

bool Sprite::CollidingWith(const Sprite& other) const
{
	if (texture == nullptr || other.texture == nullptr)
		return false;
	return Distance(other) < Radius() * other.Radius();
}

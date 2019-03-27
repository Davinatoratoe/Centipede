#include "Sprite.h"
#include "CentipedeGameApp.h"

Sprite::Sprite()
{
	texture = nullptr;
	app = CentipedeGameApp::instance;
}

Sprite::~Sprite()
{
	if (texture != nullptr)
		delete texture;
}

float Sprite::Radius() const
{
	if (texture == nullptr)
		return 0;
	return (float)((texture->getWidth() + texture->getHeight() / 2) / 2);
}

float Sprite::Distance(const Sprite& other) const
{
	return sqrt(pow(other.position.x - position.x, 2) + pow(other.position.y - position.y, 2));
}

bool Sprite::CollidingWith(const Sprite& other) const
{
	if (texture == nullptr || other.texture == nullptr)
		return false;
	return Distance(other) < Radius() * other.Radius();
}

void Sprite::Update(float deltaTime, Input* input)
{

}

void Sprite::Draw(Renderer2D* renderer)
{
	if (texture == nullptr)
		return;

	renderer->drawSprite(texture, position.x, position.y);
}

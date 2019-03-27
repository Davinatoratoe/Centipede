#pragma once
#include "Texture.h"
#include "Renderer2D.h"
#include "Input.h"
#include "Point2D.h"

using namespace aie;

class CentipedeGameApp;

class Sprite
{
public:
	Sprite();
	~Sprite();
	
	Texture* texture;
	Point2D position;
	CentipedeGameApp* app;

	float Radius() const;
	float Distance(const Sprite& other) const;
	bool CollidingWith(const Sprite& other) const;

	virtual void Update(float deltaTime, Input* input);
	virtual void Draw(Renderer2D* renderer);
};


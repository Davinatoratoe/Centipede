#pragma once
#include "Texture.h"
#include "Point2D.h"

using namespace aie;

class Sprite
{
public:
	Sprite();
	~Sprite();
	
	Texture* texture;
	Point2D position;

	int Radius() const;
	int Distance(const Sprite& other) const;
	bool CollidingWith(const Sprite& other) const;
};


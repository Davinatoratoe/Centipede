#pragma once
#include "Texture.h"
#include "Renderer2D.h"
#include "Input.h"
#include "Point2D.h"

using namespace aie;

class CentipedeGameApp;
template <typename T> class List;
template <typename T> class Dequeue;
template <typename T, typename G> struct Tuple;

class Sprite
{
public:
	Sprite();		//Default constructor
	Sprite(Texture* _texture);						//Overloaded constructors
	Sprite(Texture* _texture, float x, float y);
	Sprite(float x, float y);
	~Sprite();		//Deconstructor
	
	Texture* texture;			//Pointer to the texture that the sprite uses
	Point2D position;			//The position that the sprite will be drawn on-screen
	CentipedeGameApp* app;		//Pointer to the app
	
	//Get the radius of the sprite using the texture's dimensions
	float Radius() const;
	
	//Get the distance between this sprite and another sprite using the positions
	float Distance(const Sprite& other) const;
	
	//Get whether this sprite is colliding with another sprite using circle collision detection
	bool CollidingWith(const Sprite& other) const;

	//Update the sprite and handle input if needed
	virtual void Update(float deltaTime, Input* input);
	
	//Draw the sprite
	virtual void Draw(Renderer2D* renderer);
};


/*
	File: Centipede.h
	Contains: Segment, Centipede, CentipedeController
*/

#pragma once
#include "Sprite.h"
#include "DynamicList.h"
#include "LinkedList.h"

/// <summary>
/// A segment of a centipede.
/// </summary>
class Segment : public Sprite
{
public:
	Segment(float x, float y, bool isHead, bool isTail);	//Overloaded constructor
	~Segment();	//Deconstructor

	//Set this segment as the head (change the sprite)
	void SetHead();

	//Set this segment as the tail (change the sprite)
	void SetTail();

	//Rotate the segment to face the direction of movement
	void RotateToFace();

	//Update the segment
	void Update(float deltaTime, Input* input) override;

	//Draw the segment to the screen
	void Draw(Renderer2D* renderer) override;
};

/// <summary>
/// A centipede consisting of segments.
/// </summary>
class Centipede
{
public:
	LinkedList<Segment*>* segments;	//The segments of the centipede
	int direction;					//The horizontal direction to move the head
	unsigned int moveDown;			//Whether to move the head down
	float moveTimer = 0;			//Timer to delay movements

	const float MOVE_TIME = 0.032f;	//The time to delay movements

	Centipede();	//Default constructor
	Centipede(float x, float y, unsigned int length); //Overloaded constructor
	~Centipede();	//Deconstructor

	//Movement
	void Move(float deltaTime);
	void MoveHead(float deltaTime);

	//Create a centipede
	void CreateCentipede(float x, float y, unsigned int length);

	//Destroy a segment
	Centipede* DestroySegment(Segment* segment);
	
	//Collision detection
	bool CheckForMushroom(bool destroy);
	Segment* CheckForBullet(Sprite** _bullet) const;

	//Update the centipede
	void Update(float deltaTime, Input* input);

	//Draw the centipede to the screen
	void Draw(Renderer2D* renderer);
};

/// <summary>
/// Controller of the centipedes.
/// </summary>
class CentipedeController
{
public:
	List<Centipede*>* centipedes;	//List of centipedes

	CentipedeController();	//Default constructor
	~CentipedeController();	//Deconstructor

	//Reset all the centipedes and make 1
	void Reset(float x, float y, unsigned int length);

	//Called once per frame
	void Update(float deltaTime, Input* input);

	//Draws the centipedes
	void Draw(Renderer2D* renderer);
};


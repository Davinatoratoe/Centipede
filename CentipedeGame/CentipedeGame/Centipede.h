#pragma once
#include "Sprite.h"
#include "DynamicList.h"
#include "LinkedList.h"

class Segment : public Sprite
{
public:
	Segment(float x, float y);	//Default constructor
	~Segment();	//Deconstructor

	//Update the segment
	void Update(float deltaTime, Input* input) override;

	//Draw the segment to the screen
	void Draw(Renderer2D* renderer) override;
};

class Centipede
{
public:
	LinkedList<Segment*>* segments;
	LinkedList<Point2D>* headPath;
	int direction;
	bool moveDown;
	float moveTimer = 0;

	const float MOVE_TIME = 0.5f;

	Centipede();	//Default constructor
	~Centipede();	//Deconstructor

	void Move(float deltaTime);

	void MoveHead(float deltaTime);

	void CreateCentipede(float x, float y, unsigned int length);

	Centipede* DestroySegment(Segment* segment);

	//Update the centipede
	void Update(float deltaTime, Input* input);

	//Draw the centipede to the screen
	void Draw(Renderer2D* renderer);
};

class CentipedeController
{
public:
	List<Centipede*>* centipedes;

	CentipedeController();
	~CentipedeController();

	void Reset(float x, float y, unsigned int length);

	void Update(float deltaTime, Input* input);
	void Draw(Renderer2D* renderer);
};


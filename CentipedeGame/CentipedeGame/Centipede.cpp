#include "Centipede.h"
#include "CentipedeGameApp.h"
#include "Point2D.h"
#include <math.h>

/// <summary>
/// Default constructor.
/// </summary>
Centipede::Centipede()
{
	segments = new LinkedList<Segment*>();
	direction = 1;
	moveDown = false;
}

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="x">The starting x position of the head.</param>
/// <param name="y">The starting y position of the head.</param>
/// <param name="length">The initial length of the centipede.</param>
Centipede::Centipede(float x, float y, unsigned int length) 
{
	segments = new LinkedList<Segment*>();
	direction = 1;
	moveDown = false;

	CreateCentipede(x, y, length);
}

/// <summary>
/// Deconstructor.
/// </summary>
Centipede::~Centipede()
{
	delete segments;
}

/// <summary>
/// Moves the head of the centipede.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
void Centipede::MoveHead(float deltaTime)
{
	if (segments->Size() == 0)
		return;

	//If the head should move down then move vertically
	if (moveDown)
	{
		//Move down
		(*segments).First()->position.y -= (*segments).First()->texture->getHeight();
		moveDown = false;
	}
	//Move horizontally
	else
		(*segments).First()->position.x += ((int)((*segments).First()->texture->getWidth()) * direction);
}

/// <summary>
/// Moves the centipede.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
void Centipede::Move(float deltaTime)
{
	//If there are no segments then return
	if (segments->Size() == 0)
		return;

	//Store the old head position
	Point2D oldPosition = (*segments).First()->position;

	//Move the head
	MoveHead(deltaTime);

	//Loop through all the segments (excluding the head)
	for (auto i = (++(*segments).Begin()); i != (*segments).End(); ++i)
	{
		//Store the old position
		Point2D position = oldPosition;

		//Set the old position
		oldPosition = (*i)->position;

		//Move by the stored position
		(*i)->position = position;
	}

	//Rotate the head and tail to face the direction they're moving
	segments->First()->RotateToFace();
	if (segments->Size() > 1)
		segments->Last()->RotateToFace();

	//Reset the move timer
	moveTimer = MOVE_TIME;
}

/// <summary>
/// Create a centipede with at a location with a given length.
/// </summary>
/// <param name="x">The starting x position of the head.</param>
/// <param name="y">The starting y position of the head.</param>
/// <param name="length">The initial length of the centipede.</param>
void Centipede::CreateCentipede(float x, float y, unsigned int length)
{
	//If the length is under 3 then return
	if (length == 0 || segments->Size() > 0)
		return;

	//Find the width of a segment for use in later calculations
	unsigned int segmentWidth = CentipedeGameApp::instance->segmentTexture->getWidth();

	//Loop through the desired length and keep adding segments
	for (unsigned int i = 0; i < length; ++i)
		segments->PushBack(new Segment(x - (segmentWidth * i), y, i == 0, i == length - 1));
}

/// <summary>
/// Destroy a segment and split the centipede in half if appropriate.
/// </summary>
/// <param name="segment">The segment to destroy.</param>
/// <returns>A new centipede if this one is split in two.</returns>
Centipede* Centipede::DestroySegment(Segment* segment)
{
	return nullptr;
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
/// <param name="input">A pointer to the input handle.</param>
void Centipede::Update(float deltaTime, Input* input)
{
	if (segments->Size() == 0)
		return;

	//Update all the segments
	for (auto i = (*segments).Begin(); i != (*segments).End(); ++i)
		(*i)->Update(deltaTime, input);

	//Get the head of the centipede
	Segment* head = (*segments).First();

	//If the head has hit the left side of the screen, then move down and switch direction
	if (head->position.x < head->Radius())	
	{
		head->position.x = head->Radius();
		direction = 1;
		moveDown = true;
	}
	//If the head has hit the right side of the screen, then mode down and switch direction
	else if (head->position.x > head->app->getWindowWidth() - head->Radius())
	{
		head->position.x = head->app->getWindowWidth() - head->Radius();
		direction = -1;
		moveDown = true;
	}

	//Wait to move the segments
	if (moveTimer > 0)
		moveTimer -= deltaTime;
	//Move the segments
	else
		Move(deltaTime);
}

/// <summary>
/// Draw the centipedes.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void Centipede::Draw(Renderer2D* renderer)
{
	//Draw the segments
	for (auto i = (*segments).Begin(); i != (*segments).End(); ++i)
		(*i)->Draw(renderer);
}
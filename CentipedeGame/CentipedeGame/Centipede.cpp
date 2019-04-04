#include "Centipede.h"
#include "CentipedeGameApp.h"
#include "Point2D.h"

Centipede::Centipede()
{
	segments = new LinkedList<Segment*>();
	direction = 1;
	moveDown = 0;
}

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
	if (moveDown > 0)
	{
		//Move down
		(*segments).First()->position.y -= (MOVE_SPEED * deltaTime);

		//If we've gone down far enough then stop
		if ((*segments).First()->position.y < moveDown)
			moveDown = 0;
	}
	//Move horizontally
	else
		(*segments).First()->position.x += ((MOVE_SPEED * direction) * deltaTime);
}

/// <summary>
/// Moves the centipede.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
void Centipede::Move(float deltaTime)
{
	if (segments->Size() == 0)
		return;

	//Remember the old head position
	Point2D oldPosition = (*segments).First()->position;

	//Move the head
	MoveHead(deltaTime);

	//Loop through all the segments (excluding the head)
	for (auto i = (++(*segments).Begin()); i != (*segments).End(); ++i)
	{
		//Store the old position
		Point2D position = oldPosition;

		//If the segment is not the tail of the centipede
		if (i != (--(*segments).End()))
			//Remember the old position
			oldPosition = (*i)->position;

		//Move the segment to the stored position
		(*i)->position.x = position.x;
		(*i)->position.y = position.y;
	}
}

void Centipede::CreateCentipede(float x, float y, unsigned int length)
{
	//If the length is under 3 then return
	if (length == 0 || segments->Size() > 0)
		return;

	//Add the first segment at the given position
	segments->PushBack(new Segment(x, y));

	//Find the width of a segment for use in later calculations
	unsigned int segmentWidth = segments->First()->texture->getWidth();

	//Loop through the desired length and keep adding segments
	for (unsigned int i = 1; i < length; ++i)
		segments->PushBack(new Segment(x - (segmentWidth * i), y));
}

Centipede* Centipede::DestroySegment(Segment* segment)
{
	return nullptr;
}

void Centipede::Update(float deltaTime, Input* input)
{
	for (auto i = (*segments).Begin(); i != (*segments).End(); ++i)
		(*i)->Update(deltaTime, input);

	Segment* head = (*segments).First();
	if (head->position.x < head->Radius())
	{
		head->position.x = head->Radius();
		direction = -1;
		moveDown = head->position.y - head->texture->getHeight();
	}
	else if (head->position.x > head->app->getWindowWidth() - head->Radius())
	{
		head->position.x = head->app->getWindowWidth() - head->Radius();
		direction = -1;
		moveDown = head->position.y - head->texture->getHeight();
	}

	Move(deltaTime);
}

void Centipede::Draw(Renderer2D* renderer)
{
	for (auto i = (*segments).Begin(); i != (*segments).End(); ++i)
		(*i)->Draw(renderer);
}
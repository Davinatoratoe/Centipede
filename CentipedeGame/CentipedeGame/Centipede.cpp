#include "Centipede.h"
#include "CentipedeGameApp.h"
#include "GameScene.h"
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
	moveTimer = 0;
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
	moveDown = 0;

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

	Segment* head = (*segments).First();

	//If the head should move down then move vertically
	if (moveDown > 0)
	{
		//Move down
		head->position.y -= head->texture->getHeight();
		--moveDown;
	}
	else
	{
		//Move horizontally
		float movement = (float)((int)(head->texture->getWidth()) * direction);
		head->position.x += movement;

		//Check if the head is now on a mushroom, move back if it is and move down
		if (CheckForMushroom(segments->Size() > 3))
		{
			head->position.x -= movement;
			moveDown = 1;
			direction *= -1;
		}
		//If the head has hit the left side of the screen, then move down and switch direction
		else if (head->position.x < head->Radius())
		{
			head->position.x = head->Radius();
			direction = 1;
			moveDown = 2;
		}
		//If the head has hit the right side of the screen, then mode down and switch direction
		else if (head->position.x > head->app->getWindowWidth() - head->Radius())
		{
			head->position.x = head->app->getWindowWidth() - head->Radius();
			direction = -1;
			moveDown = 2;
		}
	}
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
	unsigned int moveFactor = segments->Size() > 2 ? segments->Size() : 3;
	moveTimer = MOVE_TIME - (MOVE_TIME / moveFactor);
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
	if (segment == nullptr)
		return nullptr;
	
	//Get a pointer to the game scene so we can spawn a mushroom
	GameScene* gameScene = dynamic_cast<GameScene*>(segment->app->gameScene);
	gameScene->SpawnMushroom(segment->position.x, segment->position.y);
	
	//If there is only one segment then the centipede is no more
	if (segments->Size() == 1)
		segments->Clear();
	//If the segment is the first one, then pop it
	else if (segment == segments->First())
	{
		segments->PopFront();
		segments->First()->SetHead();
	}
	//If the segment is the last one, then pop it
	else if (segment == segments->Last())
	{
		segments->PopBack();
		if (segments->Size() > 1)
			segments->Last()->SetTail();
	}
	//If the segment is inbetween the head & tail
	else
	{
		//Create a new centipede
		Centipede* centipede = new Centipede();

		//Iterator at the end of the segments
		Segment* newSegment = segments->Last();

		//Push the segments to the centipede from the back until we reach the destroyed segment
		while (true)
		{
			//Push segments behind the hit segment to the new centipede
			if (newSegment != segment)
				centipede->segments->PushBack(newSegment);
			
			//Pop the segment off this centipede (because it was added to the new one, or is the one that was hit)
			segments->PopBack();

			//Break out of the loop if we are at the segment that was hit
			if (newSegment == segment)
				break;

			//Otherwise set the segment to the new last segment on the centipede
			newSegment = segments->Last();
		}
		
		//Set the head and tail of the new centipede
		centipede->segments->First()->SetHead();
		if (centipede->segments->Size() > 1)
			centipede->segments->Last()->SetTail();

		return centipede;
	}

	//Return a nullptr - should never execute
	return nullptr;
}

/// <summary>
/// Check is the head has collided with a mushroom.
/// </summary>
/// <param name="destroy">Whether to destroy the mushroom if it was hit.</param>
/// <returns>True if the head has collided with a mushroom.</returns>
bool Centipede::CheckForMushroom(bool destroy)
{
	//Don't continue if the centipede size if 0
	if (segments->Size() == 0)
		return false;

	//Pointer to the head
	Segment* head = segments->First();

	//Pointer to the game scene
	GameScene* gameScene = dynamic_cast<GameScene*>(head->app->gameScene);

	//Pointer to the mushrooms
	List<Sprite*>* mushrooms = gameScene->mushrooms;

	//Iterate over the mushrooms and check if they are colliding with the head
	for (unsigned int i = 0; i < mushrooms->Size(); ++i)
	{
		//Pointer to a mushroom
		Sprite* mushroom = (*mushrooms)[i];

		//If the mushroom is a nullptr or is too far away from the head, continue
		if (mushroom == nullptr || mushroom->Distance(*head) > mushroom->Radius() + head->Radius())
			continue;

		//Check if the mushroom is colliding with the head and return true if it is
		if (mushroom->CollidingWith(*head))
		{
			if (destroy)
				gameScene->mushrooms->Remove(mushroom);
			return true;
		}
	}

	//Otherwise return false
	return false;
}

/// <summary>
/// Check if a segment has collided with a bullet.
/// </summary>
/// <returns>The segment that collided with a bullet.</returns>
Segment* Centipede::CheckForBullet(Sprite** _bullet) const
{
	//Don't continue if the centipede size if 0
	if (segments->Size() == 0)
		return false;

	//Pointer to the game scene
	GameScene* gameScene = dynamic_cast<GameScene*>(segments->First()->app->gameScene);

	//Pointer to the mushrooms
	List<Sprite*>* bullets = gameScene->player->bullets;

	//Iterate over the mushrooms and check if they are colliding with the head
	for (unsigned int i = 0; i < bullets->Size(); ++i)
	{
		for (auto segment = segments->Begin(); segment != segments->End(); ++segment)
		{
			//Pointer to a mushroom
			Sprite* bullet = (*bullets)[i];

			//If the mushroom is a nullptr or is too far away from the head, continue
			if (bullet == nullptr || bullet->Distance(**segment) > bullet->Radius() + segment->Radius())
				continue;

			//Check if the mushroom is colliding with the head and return true if it is
			if (bullet->CollidingWith(**segment))
			{
				*_bullet = bullet;
				return *segment;
			}
		}
	}

	//Otherwise return false
	return nullptr;
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
/// <param name="input">A pointer to the input handle.</param>
void Centipede::Update(float deltaTime, Input* input)
{
	//Don't update if the centipede has no segments
	if (segments->Size() == 0)
		return;

	//Update all the segments
	for (auto i = (*segments).Begin(); i != (*segments).End(); ++i)
		(*i)->Update(deltaTime, input);

	//Get the head of the centipede
	Segment* head = (*segments).First();

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
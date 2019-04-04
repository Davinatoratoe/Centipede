#include "Centipede.h"

/// <summary>
/// Default constructor.
/// </summary>
CentipedeController::CentipedeController()
{
	centipedes = new List<Centipede*>();
}

/// <summary>
/// Deconstructor.
/// </summary>
CentipedeController::~CentipedeController()
{
	delete centipedes;
}

/// <summary>
/// Reset everything so there is one centipede.
/// </summary>
/// <param name="x">The initial x position of the head of the centipede.</param>
/// <param name="y">The initial y position of the head of the centipede.</param>
/// <param name="length">The length of the centipede.</param>
void CentipedeController::Reset(float x, float y, unsigned int length)
{
	//Clear the current centipedes
	centipedes->Clear();

	//Push a new centipede
	centipedes->Push(new Centipede(x, y, length));
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void CentipedeController::Update(float deltaTime, Input* input)
{
	for (unsigned int i = 0; i < centipedes->Size(); ++i)
		(*centipedes)[i]->Update(deltaTime, input);
}

/// <summary>
/// Draws the centipedes to screen.
/// </summary>
/// <param name="renderer">A pointer to graphics renderer.</param>
void CentipedeController::Draw(Renderer2D* renderer)
{
	//Draw the centipedes
	for (unsigned int i = 0; i < centipedes->Size(); ++i)
		(*centipedes)[i]->Draw(renderer);
}
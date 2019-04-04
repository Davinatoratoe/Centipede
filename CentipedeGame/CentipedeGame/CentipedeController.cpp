#include "Centipede.h"

CentipedeController::CentipedeController()
{
	centipedes = new List<Centipede*>();
}

CentipedeController::~CentipedeController()
{
	delete centipedes;
}

void CentipedeController::Reset(float x, float y, unsigned int length)
{
	//Clear the current centipedes
	centipedes->Clear();

	//Push a new centipede
	centipedes->Push(new Centipede());
	
	//Create the centipede
	(*centipedes)[0]->CreateCentipede(x, y, length);
}

void CentipedeController::Update(float deltaTime, Input* input)
{
	for (unsigned int i = 0; i < centipedes->Size(); ++i)
		(*centipedes)[i]->Update(deltaTime, input);
}

void CentipedeController::Draw(Renderer2D* renderer)
{
	for (unsigned int i = 0; i < centipedes->Size(); ++i)
		(*centipedes)[i]->Draw(renderer);
}
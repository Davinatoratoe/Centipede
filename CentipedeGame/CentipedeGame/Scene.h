#pragma once
#include "Input.h"
#include "Renderer2D.h"

using namespace aie;

class Scene
{
public:
	virtual void OnStart() = 0;
	virtual void OnClose() = 0;
	virtual void Update(float deltaTime, Input* input) = 0;
	virtual void Draw(Renderer2D* renderer) = 0;
};
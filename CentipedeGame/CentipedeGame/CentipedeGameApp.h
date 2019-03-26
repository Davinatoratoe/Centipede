#pragma once
#include "Application.h"
#include "Renderer2D.h"

using namespace aie;

class CentipedeGameApp : public Application {
public:

	CentipedeGameApp();
	virtual ~CentipedeGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Renderer2D*	renderer;
	Font*			font;
};
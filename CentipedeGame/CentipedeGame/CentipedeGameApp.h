#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Player.h"

using namespace aie;

class CentipedeGameApp : public Application 
{
public:
	static CentipedeGameApp* instance;

	CentipedeGameApp();
	virtual ~CentipedeGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	Renderer2D*	renderer;
	Font* font;
	Texture* shipTexture;
	Texture* bulletTexture;

	Player* player;
};
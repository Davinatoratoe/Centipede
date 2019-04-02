#pragma once
#include "Scene.h"
#include "LinkedList.h"

class LinkedListScene : public Scene
{
private:
	LinkedList<int> list;
	int value;
	Font* font;

public:
	LinkedListScene(Font* _font);
	~LinkedListScene();

	void OnStart() override;
	void OnClose() override;

	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;
};


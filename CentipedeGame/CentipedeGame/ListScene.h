#pragma once
#include "Scene.h"
#include "DynamicList.h"

class ListScene : public Scene
{
public:
	List<int> list;
	Font* font;
	int value;

	ListScene(Font* _font);
	~ListScene();

	void OnStart() override;
	void OnClose() override;

	void Update(float deltaTime, Input* input) override;
	void Draw(Renderer2D* renderer) override;
};


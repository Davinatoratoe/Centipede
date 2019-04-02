#pragma once
#include "Scene.h"
#include "DynamicList.h"

class ListScene : public Scene
{
public:
	List<int> list;		//The list to alter
	Font* font;			//The font to use
	int value;			//The value to use in the imgui box

	ListScene(Font* _font);		//Overloaded constructor
	~ListScene();				//Deconstructor

	void OnStart() override;	//Called when the scene is loaded
	void OnClose() override;	//Called when the scene is closed

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the sceen
};


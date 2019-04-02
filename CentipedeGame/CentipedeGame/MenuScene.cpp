#include "MenuScene.h"
#include "imgui.h"

using namespace ImGui;

MenuScene::MenuScene(Font* _font)
{
	font = _font;
}

MenuScene::~MenuScene()
{

}

void MenuScene::OnStart()
{
	
}

void MenuScene::OnClose()
{

}

void MenuScene::Update(float deltaTime, Input* input)
{
	if (Button("Play Centipede", ImVec2(20, 850)))
	{
		
	}
	else if (Button("Test Dynamic List", ImVec2(20, 800)))
	{

	}
}

void MenuScene::Draw(Renderer2D* renderer)
{
	
}

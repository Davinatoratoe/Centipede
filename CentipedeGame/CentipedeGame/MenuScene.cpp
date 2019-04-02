#include "MenuScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"

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
	if (Button("Play Centipede", ImVec2(150, 0)))
		app->ChangeScene(app->gameScene);
	else if (Button("Test Dynamic List", ImVec2(150, 0)))
		app->ChangeScene(app->listScene);
}

void MenuScene::Draw(Renderer2D* renderer)
{
	
}

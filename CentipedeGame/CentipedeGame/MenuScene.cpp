#include "MenuScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
MenuScene::MenuScene()
{
	
}

/// <summary>
/// Deconstructor.
/// </summary>
MenuScene::~MenuScene()
{

}

/// <summary>
/// Called when the scene loads.
/// </summary>
void MenuScene::OnStart()
{
	
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void MenuScene::OnClose()
{

}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void MenuScene::Update(float deltaTime, Input* input)
{
	if (Button("Play Centipede", ImVec2(150, 0)))		//Button to play Centipede
		app->ChangeScene(app->gameScene);
	
	if (Button("Test Dynamic List", ImVec2(150, 0)))	//Button to test Dynamic Lists
		app->ChangeScene(app->listScene);
	
	if (Button("Test Linked List", ImVec2(150, 0)))		//Button to test Linked Lists
		app->ChangeScene(app->linkedListScene);

	if (Button("Test Stack", ImVec2(150, 0)))			//Button to test Linked Lists
		app->ChangeScene(app->stackScene);

	if (Button("Test Dequeue", ImVec2(150, 0)))			//Button to test Dequeue
		app->ChangeScene(app->dequeueScene);

	if (Button("Test Binary Tree", ImVec2(150, 0)))		//Button to test Binary Trees
		app->ChangeScene(app->treeScene);

	if (Button("Test Hash Functions", ImVec2(150, 0)))	//Button to test Hash Function & Hash Tables
		app->ChangeScene(app->hashScene);

	if (Button("Exit", ImVec2(150, 0)))					//Quit the game
		app->quit();
}

/// <summary>
/// Draws the graphics.
/// </summary>
/// <param name="renderer"></param>
void MenuScene::Draw(Renderer2D* renderer)
{
	
}

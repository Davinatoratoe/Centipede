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
	//Create the title
	title = new Word("CENTIPEDE", 9, app->font, 40, 50, (float)app->getWindowHeight() - 100);
}

/// <summary>
/// Deconstructor.
/// </summary>
MenuScene::~MenuScene()
{
	delete title;
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
	//Update the title word
	title->Update(deltaTime);

	CreateGUI("Main Menu");

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

	if (Button("Test Quad Tree", ImVec2(150, 0)))		//Button to test Quad Trees
		app->ChangeScene(app->quadScene);

	if (Button("Test Binary Heap Tree", ImVec2(150, 0)))//Button to test Binary Heap Trees
		app->ChangeScene(app->heapScene);

	if (Button("Test Hash Functions", ImVec2(150, 0)))	//Button to test Hash Function & Hash Tables
		app->ChangeScene(app->hashScene);

	if (Button("Exit", ImVec2(150, 0)))					//Quit the game
		app->quit();

	End();
}

/// <summary>
/// Draws the graphics.
/// </summary>
/// <param name="renderer"></param>
void MenuScene::Draw(Renderer2D* renderer)
{
	//Draw the title word
	title->Draw(renderer);

	//Display instructions on how to play Centipede
	renderer->drawText(app->font, "How to play:", 20, 180);
	renderer->drawText(app->font, " Use <- and -> to move the ship", 20, 150);
	renderer->drawText(app->font, " Use SPACE to fire bullets", 20, 120);
	renderer->drawText(app->font, " Destroy the centipede", 20, 90);
	renderer->drawText(app->font, " You lose if the centipede", 20, 60);
	renderer->drawText(app->font, "   reaches the bottom", 20, 30);

	return;
}

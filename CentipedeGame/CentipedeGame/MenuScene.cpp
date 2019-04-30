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
	counter = 0;
	r = false;
	g = false;
	b = true;
	colourCounter = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void MenuScene::OnClose()
{
	app->setBackgroundColour(0, 0, 0);
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void MenuScene::Update(float deltaTime, Input* input)
{
	//Counter for inputting to the sin wave when changing colours
	counter += deltaTime * 0.75F;
	if (counter > 3)
	{
		counter = 0;
		++colourCounter;

		r = false;
		g = false;
		b = false;

		//Choose a new colour to fade to
		switch (colourCounter)
		{
		case 1:
			r = true;
			break;
		case 2:
			r = true;
			g = true;
			break;
		case 3:
			r = true;
			b = true;
			break;
		case 4:
			g = true;
			break;
		case 5:
			g = true;
			b = true;
			break;
		case 6:
			b = true;
			break;
		default:
			colourCounter = 0;
			r = true;
			g = true;
			b = true;
			break;
		}
	}

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
	//Set background colour
	app->setBackgroundColour(
		abs(r ? sin(counter) : 0.2F), 
		abs(g ? sin(counter) : 0.2F),
		abs(b ? sin(counter) : 0.2F)
	);
}

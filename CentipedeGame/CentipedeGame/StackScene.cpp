#include "StackScene.h"
#include "imgui.h"
#include "string"
#include "CentipedeGameApp.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
StackScene::StackScene()
{
	
}

/// <summary>
/// Deconstructor.
/// </summary>
StackScene::~StackScene()
{
}

/// <summary>
/// Called when the scene loads.
/// </summary>
void StackScene::OnStart()
{
	stack = Stack<int>();
	value = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void StackScene::OnClose()
{

}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void StackScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);

	if (Button("Generate stack", ImVec2(150, 0)))
	{
		stack.Clear();
		for (unsigned int i = 0; i < 10; ++i)
			stack.Push(rand() % 10);
	}

	if (Button("Default", ImVec2(150, 0)))
		stack = Stack<int>();

	if (Button("Push", ImVec2(150, 0)))
		stack.Push(value);

	if (Button("Pop", ImVec2(150, 0)))
		stack.Pop();

	if (Button("Clear", ImVec2(150, 0)))
		stack.Clear();

	if (Button("Stack(Capacity)", ImVec2(150, 0)))
		stack = Stack<int>(value);

	if (Button("Copy", ImVec2(150, 0)))
		stack = Stack<int>(stack);

	if (Button("Assign", ImVec2(150, 0)))
		stack = stack;

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draws the graphics.
/// </summary>
/// <param name="renderer"></param>
void StackScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(app->font, ("List: " + stack.ToString()).c_str(), 20, 850);
	renderer->drawText(app->font, ("Size: " + to_string(stack.Size())).c_str(), 20, 800);
	renderer->drawText(app->font, ("Capacity: " + to_string(stack.Capacity())).c_str(), 20, 750);
}
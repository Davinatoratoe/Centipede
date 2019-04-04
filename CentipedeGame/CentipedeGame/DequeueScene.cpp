#include "DequeueScene.h"
#include "imgui.h"
#include "string"
#include "CentipedeGameApp.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
DequeueScene::DequeueScene()
{
	
}

/// <summary>
/// Deconstructor.
/// </summary>
DequeueScene::~DequeueScene()
{
}

/// <summary>
/// Called when the scene loads.
/// </summary>
void DequeueScene::OnStart()
{
	dequeue = Dequeue<int>();
	value = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void DequeueScene::OnClose()
{

}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void DequeueScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);

	if (Button("Push Front", ImVec2(150, 0)))
		dequeue.PushFront(value);

	if (Button("Push Back", ImVec2(150, 0)))
		dequeue.PushBack(value);

	if (Button("Pop Front", ImVec2(150, 0)))
		dequeue.PopFront();

	if (Button("Pop Back", ImVec2(150, 0)))
		dequeue.PopBack();

	if (Button("Clear", ImVec2(150, 0)))
		dequeue.Clear();

	if (Button("Copy", ImVec2(150, 0)))
		dequeue = Dequeue<int>(dequeue);

	if (Button("Assign", ImVec2(150, 0)))
		dequeue = dequeue;

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draws the graphics.
/// </summary>
/// <param name="renderer"></param>
void DequeueScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(app->font, ("List: " + dequeue.ToString()).c_str(), 20, 850);
	renderer->drawText(app->font, ("Size: " + to_string(dequeue.Size())).c_str(), 20, 800);
}

#include "ListScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
ListScene::ListScene()
{
	
}

/// <summary>
/// Deconstructor.
/// </summary>
ListScene::~ListScene()
{

}

/// <summary>
/// Called when the scene starts.
/// </summary>
void ListScene::OnStart()
{
	list = List<int>();
	value = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void ListScene::OnClose()
{
	
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void ListScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);

	if (Button("Push", ImVec2(150, 0)))
		list.Push(value);
	
	if (Button("Pop", ImVec2(150, 0)))
		list.Pop();

	if (Button("Clear", ImVec2(150, 0)))
		list.Clear();

	if (Button("Reserve", ImVec2(150, 0)))
		list.Reserve(value);

	if (Button("List(Capacity)", ImVec2(150, 0)))
		list = List<int>(value);

	if (Button("Copy", ImVec2(150, 0)))
		list = List<int>(list);

	if (Button("Assign", ImVec2(150, 0)))
		list = list;

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draw the list to the screen.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void ListScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(app->font, ("List: " + list.ToString()).c_str(), 20, 850);
	renderer->drawText(app->font, ("Size: " + to_string(list.Size())).c_str(), 20, 800);
	renderer->drawText(app->font, ("Capacity: " + to_string(list.Capacity())).c_str(), 20, 750);
}

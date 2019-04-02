#include "LinkedListScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"
#include "string"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
LinkedListScene::LinkedListScene(Font* _font)
{
	font = _font;
}

/// <summary>
/// Deconstructor.
/// </summary>
LinkedListScene::~LinkedListScene()
{

}

/// <summary>
/// Called when the scene starts.
/// </summary>
void LinkedListScene::OnStart()
{
	list = LinkedList<int>();
	value = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void LinkedListScene::OnClose()
{

}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void LinkedListScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);

	if (Button("Push to front", ImVec2(150, 0)))
		list.PushFront(value);

	if (Button("Push to back", ImVec2(150, 0)))
		list.PushBack(value);

	if (Button("Pop front", ImVec2(150, 0)))
		list.PopFront();

	if (Button("Pop back", ImVec2(150, 0)))
		list.PopBack();

	if (Button("Remove", ImVec2(150, 0)))
		list.Remove(value);

	if (Button("Clear", ImVec2(150, 0)))
		list.Clear();

	if (Button("Copy", ImVec2(150, 0)))
		list = LinkedList<int>(list);

	if (Button("Assign", ImVec2(150, 0)))
		list = list;

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draw the list to the screen.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void LinkedListScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(font, ("List: " + list.ToString()).c_str(), 20, 850);
	renderer->drawText(font, ("Size: " + to_string(list.Size())).c_str(), 20, 800);
}

#include "LinkedListScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"
#include "string"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
LinkedListScene::LinkedListScene()
{
	
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
	iterator = list.End();
	iteratorPosition = 0;
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

	if (Button("Generate list", ImVec2(200, 0)))
	{
		list.Clear();
		for (unsigned int i = 0; i < 10; ++i)
			list.PushFront(rand() % 10);
	}

	if (Button("Push to front", ImVec2(200, 0)))
		list.PushFront(value);

	if (Button("Push to back", ImVec2(200, 0)))
		list.PushBack(value);

	if (Button("Pop front", ImVec2(200, 0)))
		list.PopFront();

	if (Button("Pop back", ImVec2(200, 0)))
		list.PopBack();

	if (Button("Set iterator to Begin()", ImVec2(200, 0)))
	{
		iterator = list.Begin();
		iteratorPosition = 0;
	}

	if (Button("Set iterator to End()", ImVec2(200, 0)))
	{
		iterator = list.End();
		iteratorPosition = list.Size();
	}

	if (Button("Increase iterator", ImVec2(200, 0)) && iterator != list.End())
	{
		++iterator;
		++iteratorPosition;
	}

	if (Button("Decrease iterator", ImVec2(200, 0)) && iterator != list.Begin())
	{
		--iterator;
		--iteratorPosition;
	}

	if (Button("Insert @ iterator", ImVec2(200, 0)))
		list.Insert(iterator, value);

	if (Button("Remove", ImVec2(200, 0)))
		list.Remove(value);

	if (Button("Erase @ iterator", ImVec2(200, 0)))
	{
		list.Erase(iterator);
		iterator = list.End();	//Set to end() otherwise spews random memory
	}

	if (Button("Clear", ImVec2(200, 0)))
		list.Clear();

	if (Button("Bubble Sort", ImVec2(200, 0)))
		list.BubbleSort();

	if (Button("Copy", ImVec2(200, 0)))
		list = LinkedList<int>(list);

	if (Button("Assign", ImVec2(200, 0)))
		list = list;

	if (Button("Menu", ImVec2(200, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draw the list to the screen.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void LinkedListScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(app->font, ("List: " + list.ToString()).c_str(), 20, 850);
	renderer->drawText(app->font, ("Size: " + to_string(list.Size())).c_str(), 20, 800);
	
	ostringstream stream;
	stream << "Iterator value: ";
	if (iterator == list.End())
		stream << "End()";
	else
		stream << *iterator;
	stream << "    Position: " << iteratorPosition;
	renderer->drawText(app->font, stream.str().c_str(), 20, 750);
}

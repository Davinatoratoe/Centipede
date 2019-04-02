#include "ListScene.h"
#include "imgui.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use to display information.</param>
ListScene::ListScene(Font* _font)
{
	font = _font;
}

/// <summary>
/// Deconstructor.
/// </summary>
ListScene::~ListScene()
{

}

/// <summary>
/// Called when the scene is loaded.
/// </summary>
void ListScene::OnStart()
{
	list = List<int>();
	value = 0;
}

/// <summary>
/// Called when the scene is closed.
/// </summary>
void ListScene::OnClose()
{
	
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has elapsed since last frame.</param>
/// <param name="input">Pointer to the input handler.</param>
void ListScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);	//Allow the user to enter a number and store in value

	if (Button("Push", ImVec2(150, 0)))	//Create a button that pushes a value to the list
		list.Push(value);
	
	if (Button("Pop", ImVec2(150, 0)))	//Create a button that pops the last value off the list
		list.Pop();

	if (Button("Clear", ImVec2(150, 0)))	//Create a button that clears the list
		list.Clear();

	if (Button("Reserve", ImVec2(150, 0)))	//Create a button that reserves more capacity
		list.Reserve(value);

	if (Button("Create(capacity)", ImVec2(150, 0)))	//Create a button that will create a new list with a capacity
		list = List<int>(value);

	if (Button("Create(copy)", ImVec2(150, 0)))	//Create a list using the copy constructor
		list = List<int>(list);

	if (Button("Assign", ImVec2(150, 0)))	//Assign the list to a list using the assignment operator
		list = list;
}

void ListScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(font, ("List: " + list.ToString()).c_str(), 20, 850);
	renderer->drawText(font, ("Size: " + to_string(list.Size())).c_str(), 20, 800);
	renderer->drawText(font, ("Capacity: " + to_string(list.Capacity())).c_str(), 20, 750);
}
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
	searchResult = -1;
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

	if (Button("Generate list", ImVec2(250, 0)))
	{
		list.Clear();
		for (unsigned int i = 0; i < 10; ++i)
			list.Push(rand() % 10);
	}

	if (Button("Push", ImVec2(250, 0)))
		list.Push(value);

	if (Button("Insert #size @ value", ImVec2(250, 0)))
		list.Insert(value, list.Size());
	
	if (Button("Insert list @ value", ImVec2(250, 0)))
		list.Insert(value, List<int>(list));

	if (Button("Pop", ImVec2(250, 0)))
		list.Pop();

	if (Button("Clear", ImVec2(250, 0)))
		list.Clear();

	if (Button("Reserve", ImVec2(250, 0)))
		list.Reserve(value);

	if (Button("Discard", ImVec2(250, 0)))
		list.Discard(value);

	if (Button("Remove index (no order)", ImVec2(250, 0)))
		list.Remove((unsigned int)value);

	if (Button("Remove index (order)", ImVec2(250, 0)))
		list.RemoveKeepOrder((unsigned int)value);

	if (Button("Quick Sort", ImVec2(250, 0)))
		list.QuickSort();

	if (Button("Cocktail Shaker Sort", ImVec2(250, 0)))
		list.CocktailShakerSort();

	if (Button("Insertion Sort", ImVec2(250, 0)))
		list.InsertionSort();

	if (Button("Fibonacci Search(value)", ImVec2(250, 0)))
		searchResult = list.FibonacciSearch(value);

	if (Button("Binary Search(value)", ImVec2(250, 0)))
		searchResult = list.BinarySearch(value);

	if (Button("List(Capacity)", ImVec2(250, 0)))
		list = List<int>(value);

	if (Button("Copy constructor", ImVec2(250, 0)))
		list = List<int>(list);

	if (Button("Assignment operator", ImVec2(250, 0)))
		list = list;

	if (Button("Menu", ImVec2(250, 0)))
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
	renderer->drawText(app->font, ("Search result: " + to_string(searchResult)).c_str(), 20, 700);
}

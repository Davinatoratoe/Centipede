#include "HeapScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"
#include <string>

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
HeapScene::HeapScene()
{

}

/// <summary>
/// Deconstructor.
/// </summary>
HeapScene::~HeapScene()
{

}

/// <summary>
/// Called when the scene loads.
/// Sets initial values.
/// </summary>
void HeapScene::OnStart()
{
	heap = Heap<int>();
	selectedIndex = -1;
	value = 0;
	oldMouseScroll = Input::getInstance()->getMouseScroll();
	treeX = 0;
	treeY = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void HeapScene::OnClose()
{
	//Reset the camera position and scale
	app->renderer->setCameraPos(0, 0);
	app->renderer->setCameraScale(1);
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that has passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void HeapScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);

	if (Button("Generate heap", ImVec2(150, 0)))	//Create a template heap to mess around with
	{
		heap.Clear();
		for (unsigned int i = 0; i < 10; ++i)
			heap.Push(rand() % 100);
	}

	if (Button("Push", ImVec2(150, 0)))		//Push a value into the heap
	{
		heap.Push(value);
		selectedIndex = heap.Find(value);
	}

	if (Button("Remove", ImVec2(150, 0)))	//Remove a value from the tree
	{
		heap.Remove(value);
		selectedIndex = heap.Find(value);
	}

	if (Button("Find", ImVec2(150, 0)))
		selectedIndex = heap.Find(value);

	if (Button("Clear", ImVec2(150, 0)))	//Clear all values from the tree
	{
		heap.Clear();
		selectedIndex = -1;
	}

	if (Button("Copy", ImVec2(150, 0)))		//Call the copy constructor
		heap = Heap<int>(heap);

	if (Button("Assign", ImVec2(150, 0)))	//Call the assignment operator
		heap = heap;

	if (Button("Menu", ImVec2(150, 0)))		//Return to the main menu
		app->ChangeScene(app->menuScene);

	float mouseScroll = (float)(input->getMouseScroll() - oldMouseScroll) * ZOOM_FACTOR;	//Get how much the mouse scrolled since last frame
	oldMouseScroll = input->getMouseScroll();	//Remember how far it was scrolled to use in next frame's calculation
	app->renderer->setCameraScale(app->renderer->getCameraScale() + mouseScroll);	//Change the camera scale when the user scrolls

	//Move the camera when the user presses the arrow keys
	if (input->isKeyDown(INPUT_KEY_DOWN))
		treeY += MOVE_SPEED;
	else if (input->isKeyDown(INPUT_KEY_UP))
		treeY -= MOVE_SPEED;
	if (input->isKeyDown(INPUT_KEY_LEFT))
		treeX += MOVE_SPEED;
	else if (input->isKeyDown(INPUT_KEY_RIGHT))
		treeX -= MOVE_SPEED;

	//Alternatively, move the camera when the user clicks and drags the mouse
	if (input->isMouseButtonDown(1))
	{
		treeX += input->getMouseDeltaX();
		treeY += input->getMouseDeltaY();
	}
}

/// <summary>
/// Draw the scene.
/// </summary>
/// <param name="renderer">A pointer to the renderer used to display graphics.</param>
void HeapScene::Draw(Renderer2D* renderer)
{
	//Draw the tree recursively
	DrawTree(renderer, heap.GetRootIndex() , 370 + treeX, 850 + treeY, 400, selectedIndex);

	//Display the size and number of edges
	renderer->drawText(app->font, ("Size: " + to_string(heap.Size())).c_str(), 50, 50);
	renderer->drawText(app->font, "Zoom with mouse scroll wheel...", 50, 100);
	renderer->drawText(app->font, "Move with WASD or right-click & drag...", 50, 150);
}

/// <summary>
/// Recursively draw the tree.
/// Implementation based off the Binary Trees Tutorial.
/// </summary>
/// <param name="renderer">A pointer to the renderer used to draw graphics.</param>
/// <param name="node">The index of the node to draw.</param>
/// <param name="x">The x-position to draw the node.</param>
/// <param name="y">The y-position to draw the node.</param>
/// <param name="horizontalSpacing">The spacing between the nodes.</param>
/// <param name="selected">The index of the node that is selected (highlighted).</param>
void HeapScene::DrawTree(Renderer2D* renderer, unsigned int index, float x, float y, int horizontalSpacing, unsigned int selectedIndex) const
{
	horizontalSpacing /= 2;

	if (index != -1)	//If the node exists in the heap
	{
		if (heap.HasFirstChild(index))	//If there is a first child, then draw it recursively
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			DrawTree(renderer, heap.GetFirstChild(index), x - horizontalSpacing, y - 80, horizontalSpacing, selectedIndex);
		}
		if (heap.HasSecondChild(index))	//If there is a second child, then draw it recursively
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			DrawTree(renderer, heap.GetSecondChild(index), x + horizontalSpacing, y - 80, horizontalSpacing, selectedIndex);
		}

		//Draw the circle for the node
		renderer->setRenderColour(1, 1, 0);
		renderer->drawCircle(x, y, 30);

		//If the node is the one selected, fill in the circle
		if (selectedIndex == index)
			renderer->setRenderColour(0.5, 0.5, 0);
		else
			renderer->setRenderColour(0, 0, 0);
		renderer->drawCircle(x, y, 28);

		//Draw the value in the node
		renderer->setRenderColour(1, 1, 1);
		renderer->drawText(app->font, to_string(heap[index]).c_str(), x - 12, y - 10);
	}
}

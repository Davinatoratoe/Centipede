/*
	File: HeapScene.h
	Contains: HeapScene
*/

#pragma once
#include "Scene.h"
#include "BinaryHeap.h"

/// <summary>
/// The Binary Heap Scene allows manipulating a binary heap structure visually.
/// </summary>
class HeapScene : public Scene
{
private:
	Heap<int> heap;					//The heap to manipulate
	int selectedIndex;				//Index of the node that is highlighted
	int value;						//The value to manipulate
	double oldMouseScroll;			//How far the mouse was scrolled in the previous frame
	float treeX;					//The amount to offset the tree draw position on the x-axis
	float treeY;					//The amount to offset the tree draw position on the y-axis

	const float ZOOM_FACTOR = 0.1f;		//The factor to zoom in and out by
	const unsigned int MOVE_SPEED = 5;	//The speed to move the camera

	//Recursive function to draw the tree graphically
	void DrawTree(Renderer2D* renderer, unsigned int index, float x, float y, int horizontalSpacing, unsigned int selectedIndex = -1) const;

public:
	HeapScene();		//Overloaded constructor
	~HeapScene();		//Deconstructor

	void OnStart() override;		//Called when the scene is loaded
	void OnClose() override;		//Called when the scene is closed

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the scene
};


/*
	File: LinkedListScene.h
	Contains: LinkedListScene
*/

#pragma once
#include "Scene.h"
#include "LinkedList.h"

/// <summary>
/// The Linked List Scene allows manipulating and displaying a linked list
/// </summary>
class LinkedListScene : public Scene
{
private:
	LinkedList<int> list;	//The Linked List to manipulate
	int value;				//The value to manipulate
	LinkedList<int>::LinkedListIterator<int> iterator;	//Iterator used to traverse the linked list
	unsigned int iteratorPosition;	//Position of the iterator
	LinkedList<int>::LinkedListIterator<int> searchResult;	//Iterator used for searching the linked list

public:
	LinkedListScene();	//Overloaded constructor
	~LinkedListScene();	//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the graphics of the scene
};


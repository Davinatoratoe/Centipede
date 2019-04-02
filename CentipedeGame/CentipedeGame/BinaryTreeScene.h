/*
	File: BinaryTreeScene.h
	Contains: BinaryTreeScene
*/

#pragma once
#include "Scene.h"
#include "BinaryTree.h"

/// <summary>
/// The Binary Tree Scene allows manipulating a binary tree structure visually.
/// </summary>
class BinaryTreeScene : public Scene
{
private:
	BinaryTree<int> tree;			//The tree to manipulate
	BinaryTreeNode<int>* selected;	//The selected node
	Font* font;						//The font to use
	int value;						//The value to manipulate
	double oldMouseScroll;			//How far the mouse was scrolled in the previous frame
	int treeX;						//The amount to offset the tree draw position on the x-axis
	int treeY;						//The amount to offset the tree draw position on the y-axis
	
	const double ZOOM_FACTOR = 0.1;		//The factor to zoom in and out by
	const unsigned int MOVE_SPEED = 5;	//The speed to move the camera

	//Recursive function to draw the tree graphically
	void DrawTree(Renderer2D* renderer, BinaryTreeNode<int>* node, int x, int y, int horizontalSpacing, BinaryTreeNode<int>* selected = nullptr) const;

public:
	BinaryTreeScene(Font* _font);	//Overloaded constructor
	~BinaryTreeScene();				//Deconstructor

	void OnStart() override;		//Called when the scene is loaded
	void OnClose() override;		//Called when the scene is closed

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Draws the scene
};


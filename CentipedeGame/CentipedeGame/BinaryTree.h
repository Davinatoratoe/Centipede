#pragma once
#include <iostream>

using namespace std;

template <typename T>
class BinaryTreeNode
{
public:
	T* data;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;
};

template <typename T>
class BinaryTree
{

};
/*
	File: BinaryTree.h
	Contains: BinaryTree, BinaryTreeNode
*/

#pragma once
#include <iostream>
#include <queue>	//Change to custom implementation

using namespace std;

/// <summary>
/// The Binary Tree Node class represents a node in the binary tree.
/// Each node has a piece of data attached and a pointer to the left & right child.
/// </summary>
template <typename T>
class BinaryTreeNode
{
public:
	T data;						//The data attached to this node
	BinaryTreeNode<T>* left;	//Pointer to the left child
	BinaryTreeNode<T>* right;	//Pointer to the right child

	/// <summary>
	/// Overloaded constructor.
	/// </summary>
	/// <param name="_data">The data to attach to this node.</param>
	BinaryTreeNode(const T& _data)
	{
		data = _data;
		left = nullptr;
		right = nullptr;
	}

	/// <summary>
	/// Overloaded constructor.
	/// </summary>
	/// <param name="_data">The data to attach to this node.</param>
	/// <param name="_left">A pointer to the left child.</param>
	/// <param name="_right">A pointer to the right child.</param>
	BinaryTreeNode(const T& _data, const BinaryTreeNode<T>* _left, const BinaryTreeNode<T>* _right)
	{
		data = _data;
		left = _left;
		right = _right;
	}

	/// <summary>
	/// Deconstructor.
	/// </summary>
	~BinaryTreeNode() {}
};

//Enum for choosing how to use the depth search on the binary tree
enum DEPTH_FIRST_SEARCH_TYPE { SEARCH_PRE_ORDER, SEARCH_POST_ORDER, SEARCH_IN_ORDER };

/// <summary>
/// The Binary Tree class has a root node and keeps track of the number of nodes.
/// </summary>
template <typename T>
class BinaryTree
{
private:
	typedef void(*ProcessFnType)(BinaryTreeNode<T>* node);	//Function type definition for use in the search functions
	BinaryTreeNode<T>* root;	//The root node of the tree
	unsigned int size;			//The number of nodes in the tree

public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	BinaryTree()
	{
		root = nullptr;
		size = 0;
	}

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="copy">The tree to copy.</param>
	BinaryTree(const BinaryTree& copy)
	{
		
	}

	/// <summary>
	/// Deconstructor.
	/// </summary>
	~BinaryTree()
	{
		Clear();
	}

	/// <summary>
	/// Insert a new node into the tree in the correct position.
	/// If the node already exists, no changes will be made.
	/// </summary>
	/// <param name="data">The data to add to the tree.</param>
	void Insert(const T& data)
	{
		if (Empty())	//If the tree is empty then set up the root
		{
			root = new BinaryTreeNode<T>(data);
			size = 1;
		}
		else
		{
			BinaryTreeNode<T>* node = root;			//Keep track of the current node and its parent
			BinaryTreeNode<T>* parent = nullptr;
			while (node != nullptr)
			{
				parent = node;
				if (data < node->data)				//If the data is less than the data of this node, then traverse to the left child
					node = node->left;
				else if (data > node->data)			//If the data is greater than the data of this node, then traverse to the right child
					node = node->right;
				else								//If the data already exists, exit the function
					return;
			}

			//Attach a new node as a leaf to the parent
			if (data < parent->data)
				parent->left = new BinaryTreeNode<T>(data);
			else
				parent->right = new BinaryTreeNode<T>(data);
			++size;
		}
	}

	/// <summary>
	/// Remove a node from the tree.
	/// </summary>
	/// <param name="data">The data to remove from the tree.</param>
	void Remove(const T& data)
	{
		if (Empty())			//If the tree is empty, then return
			return;
		else if (size == 1)		//If the tree only contains the root then just delete the root
		{
			delete root;
			root = nullptr;
			size = 0;
		}
		else
		{
			BinaryTreeNode<T>** ppNode = new BinaryTreeNode<T>*;
			BinaryTreeNode<T>** ppParent = new BinaryTreeNode<T>*;
			if (Find(data, ppNode, ppParent))				//If we can find the node to be removed...
			{
				BinaryTreeNode<T>* node = (*ppNode);
				BinaryTreeNode<T>* parent = (*ppParent);

				//If the the child to the right is not null,
				//Then find the smallest value in the tree that is greater than the one we want to remove
				if (node->right != nullptr)
				{
					BinaryTreeNode<T>* minimum = node->right;
					BinaryTreeNode<T>* minimumParent = node;
					
					//Find the value by traversing the left children of the right child off the node to be removed
					while (minimum->left != nullptr)
					{
						minimumParent = minimum;
						minimum = minimum->left;
					}
					node->data = minimum->data;		//Copy the data from one to the other

					//Delete the minimum node
					if (minimumParent->left == minimum)
						minimumParent->left = minimum->right;
					else
						minimumParent->right = minimum->left;
					delete minimum;
				}
				else
				{
					if (parent->left == node)		//Do we delete the parent's left child?
						parent->left = node->left;
					if (parent->right == node)		//Do we delete the parent's right child?
						parent->right = node->left;
					if (node == root)				//If the node to remove is the root, then delete it
						root = node->left;
					delete node;
				}
				--size;
			}
			delete ppNode;
			delete ppParent;
		}
	}

	/// <summary>
	/// Get a Tree Node that contains the given data value.
	/// Searches through the tree.
	/// </summary>
	/// <param name="data">The data to search for.</param>
	/// <returns>The node with the data.</returns>
	BinaryTreeNode<T>* Find(const T& data) const
	{
		BinaryTreeNode<T>** ppNode = new BinaryTreeNode<T>*;
		BinaryTreeNode<T>** ppParent = new BinaryTreeNode<T>*;
		bool found = Find(data, ppNode, ppParent);		//Try to find the node
		delete ppNode;
		delete ppParent;
		return found ? (*ppNode) : nullptr;		//Return the node if it was found
	}

	/// <summary>
	/// The function will return true if a node with the given data is present in the tree.
	/// The function will also use pointers to return additional information.
	/// </summary>
	/// <param name="data">The data to search for.</param>
	/// <param name="ppNode">The node that the data is found at.</param>
	/// <param name="ppParent">The parent of the node that the data is found at.</param>
	/// <returns>True if the node is found in the tree that matches the given data.</returns>
	bool Find(const T& data, BinaryTreeNode<T>** ppNode, BinaryTreeNode<T>** ppParent) const
	{
		*ppNode = root;					//Start at the root
		while ((*ppNode) != nullptr)	//Loop until we reach a nullptr node
		{
			if (data == (*ppNode)->data)	//If the data matches the node data, then return true
				return true;
			else
			{
				*ppParent = *ppNode;	//Update the parent node before changing the node itself
				//Traverse to the left or right node depending on the relationship between the data and the data in the current node
				*ppNode = (data < (*ppNode)->data) ? (*ppNode)->left : (*ppNode)->right;
			}
		}
		return false;	//If no node is found, then return false
	}

	/// <summary>
	/// Empties the tree.
	/// </summary>
	void Clear()
	{
		//Loop until the tree is empty
		while (!Empty())
			Remove(root->data);
		size = 0;
	}

	/// <summary>
	/// Iterate through the tree and perform a function on each node.
	/// </summary>
	/// <param name="searchType">The way to traverse through the tree. (PRE_ORDER, POST_ORDER, IN_ORDER)</param>
	/// <param name="ProcessFn">A function pointer that will process any particular node in the tree.</param>
	void DepthFirstSearch(DEPTH_FIRST_SEARCH_TYPE searchType, ProcessFnType ProcessFn)
	{
		if (!Empty())
		{
			if (searchType == SEARCH_PRE_ORDER)
				DepthFirstPreOrderSearch(root, Process);
			else if (searchType == SEARCH_POST_ORDER)
				DepthFirstPostOrderSearch(root, Process);
			else
				DepthFirstInOrderSearch(root, Process);
		}
	}

	void BreadthFirstSearch(ProcessFnType ProcessFn)
	{
		if (!Empty())
		{
			queue<BinaryTreeNode<T>*> list;
			list.push(root);
			while (!list.empty())
			{
				BinaryTreeNode<T>* node = list.front();
				ProcessFn(node);
				list.pop();
				if (node->left != nullptr)
					list.push(node->left);
				if (node->right != nullptr)
					list.push(node->right);
			}
		}
	}

	BinaryTreeNode<T>* GetRoot() const
	{
		return root;
	}

	bool Empty() const
	{
		return size == 0;
	}

	unsigned int Size()
	{
		return size;
	}

	BinaryTree<T>& operator= (const BinaryTree<T>& other)
	{
		return *this;
	}

	/// <summary>
	/// Recursively prints the tree to an ostream.
	/// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
	/// </summary>
	/// <param name="os">The ostream the print the tree to.</param>
	/// <param name="node">The current node to process. (Initially root)</param>
	/// <param name="space">The space between the levels. (Initially 0)</param>
	friend void PrintTreeF(ostream& os, BinaryTreeNode<T>* node, int space)
	{
		if (node == nullptr)
			return;

		//Increase the distance between the levels
		space += 5;

		//Process the right child
		PrintTreeF(os, node->right, space);

		//Print the current node
		os << endl;
		for (int i = 5; i < space; ++i)
			os << " ";
		os << node->data << endl;

		//Process the left child
		PrintTreeF(os, node->left, space);
	}

	/// <summary>
	/// Overloaded << operator.
	/// Displays the tree to an ostream.
	/// </summary>
	/// <param name="os">The ostream to print the tree to.</param>
	/// <param name="tree">The tree to print.</param>
	/// <returns>The ostream with the tree printed to it.</returns>
	friend ostream& operator<< (ostream& os, const BinaryTree<T>& tree)
	{
		//Call the other friend function to recursively print the tree
		PrintTreeF(os, tree.GetRoot(), 0);
		return os;
	}

	/// <summary>
	/// Print details about the tree.
	/// </summary>
	void PrintDetails() const
	{
		cout << "Size: " << size << endl;
		//Call a function to recursively print the tree to std::cout
		PrintTree(root, 0);
	}

private:
	void DepthFirstPreOrderSearch(BinaryTreeNode<T>* node, ProcessFnType ProcessFn)
	{
		ProcessFn(node);
		if (node->left != nullptr)
			DepthFirstPreOrderSearch(node->left, Process);
		if (node->right != nullptr)
			DepthFirstPreOrderSearch(node->right, Process);
	}

	void DepthFirstPostOrderSearch(BinaryTreeNode<T>* node, ProcessFnType ProcessFn)
	{
		if (node->left != nullptr)
			DepthFirstPreOrderSearch(node->left, Process);
		if (node->right != nullptr)
			DepthFirstPreOrderSearch(node->right, Process);
		ProcessFn(node);
	}

	void DepthFirstInOrderSearch(BinaryTreeNode<T>* node, ProcessFnType ProcessFn)
	{
		if (node->left != nullptr)
			DepthFirstPreOrderSearch(node->left, Process);
		ProcessFn(node);
		if (node->right != nullptr)
			DepthFirstPreOrderSearch(node->right, Process);
	}

	/// <summary>
	/// Recursively prints the tree to std::cout
	/// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
	/// </summary>
	/// <param name="node">The current node to process. (Initially root)</param>
	/// <param name="space">The space between the levels. (Initially 0)</param>
	void PrintTree(BinaryTreeNode<T>* node, int space) const
	{
		if (node == nullptr)
			return;
		
		//Increase the distance between the levels
		space += 5;

		//Process the right child
		PrintTree(node->right, space);

		//Print the current node
		cout << endl;
		for (int i = 5; i < space; ++i)
			cout << " ";
		cout << node->data << endl;

		//Process the left child
		PrintTree(node->left, space);
	}
};
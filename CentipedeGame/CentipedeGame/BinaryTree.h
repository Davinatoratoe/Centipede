#pragma once
#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class BinaryTreeNode
{
public:
	T data;
	BinaryTreeNode<T>* left;
	BinaryTreeNode<T>* right;

	BinaryTreeNode(const T& _data)
	{
		data = _data;
		left = nullptr;
		right = nullptr;
	}

	BinaryTreeNode(const T& _data, const BinaryTreeNode<T>* _left, const BinaryTreeNode<T>* _right)
	{
		data = _data;
		left = _left;
		right = _right;
	}

	~BinaryTreeNode() {}
};

enum DEPTH_FIRST_SEARCH_TYPE { SEARCH_PRE_ORDER, SEARCH_POST_ORDER, SEARCH_IN_ORDER };

template <typename T>
class BinaryTree
{
private:
	typedef void(*ProcessFnType)(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* root;
	unsigned int size;

public:
	BinaryTree()
	{
		root = nullptr;
		size = 0;
	}

	BinaryTree(const BinaryTree& copy)
	{
		size = copy.size;
	}

	~BinaryTree()
	{
		Clear();
	}

	void Insert(const T& data)
	{
		if (Empty())
		{
			root = new BinaryTreeNode<T>(data);
			size = 1;
		}
		else
		{
			BinaryTreeNode<T>* node = root;
			BinaryTreeNode<T>* parent = nullptr;
			while (node != nullptr)
			{
				parent = node;
				if (data < node->data)
					node = node->left;
				else if (data > node->data)
					node = node->right;
				else
					return;
			}

			if (data < parent->data)
				parent->left = new BinaryTreeNode<T>(data);
			else
				parent->right = new BinaryTreeNode<T>(data);
			++size;
		}
	}

	void Remove(const T& data)
	{
		if (Empty())
			return;
		else if (size == 1)
		{
			delete root;
			root = nullptr;
			size = 0;
		}
		else
		{
			BinaryTreeNode<T>** ppNode = new BinaryTreeNode<T>*;
			BinaryTreeNode<T>** ppParent = new BinaryTreeNode<T>*;
			if (Find(data, ppNode, ppParent))
			{
				BinaryTreeNode<T>* node = (*ppNode);
				BinaryTreeNode<T>* parent = (*ppParent);

				if (node->right != nullptr)
				{
					BinaryTreeNode<T>* minimum = node->right;
					BinaryTreeNode<T>* minimumParent = node;

					while (minimum->left != nullptr)
					{
						minimumParent = minimum;
						minimum = minimum->left;
					}
					node->data = minimum->data;

					if (minimumParent->left == minimum)
						minimumParent->left = minimum->right;
					else
						minimumParent->right = minimum->left;
				}
				else
				{
					if (node == root)
						root = node->left;
					else if (parent->left == node)
						parent->left = node->left;
					else if (parent->right == node)
						parent->right = node->left;
				}
				--size;
			}
		}
	}

	BinaryTreeNode<T>* Find(const T& data) const
	{
		BinaryTreeNode<T>** ppNode = new BinaryTreeNode<T>*;
		BinaryTreeNode<T>** ppParent = new BinaryTreeNode<T>*;
		if (Find(data, ppNode, ppParent))
			return (*ppNode);
		else
			return nullptr;
	}

	bool Find(const T& data, BinaryTreeNode<T>** ppNode, BinaryTreeNode<T>** ppParent) const
	{
		*ppNode = root;
		while ((*ppNode) != nullptr)
		{
			if (data == (*ppNode)->data)
				return true;
			else
			{
				*ppParent = *ppNode;
				*ppNode = (data < (*ppNode)->data) ? (*ppNode)->left : (*ppNode)->right;
			}
		}
		return false;
	}

	void Clear()
	{
		while (!Empty())
			Remove(root->data);
		size = 0;
	}

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

	bool Empty() const
	{
		return size == 0;
	}

	unsigned int Size()
	{
		return size;
	}

	void PrintDetails()
	{
		cout << "Size: " << size << endl;
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
};
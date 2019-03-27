#pragma once
#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
private:
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* next;
		Node* previous;

		Node(Node* _next, Node* _previous)
		{
			_next = next;
			_previous = previous;
		}
		Node(T _data, Node* _next, Node* _previous)
		{
			data = _data;
			next = _next;
			previous = _previous;
		}
	};

	Node* head;
	Node* tail;
	unsigned int size;

public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	~LinkedList()
	{
		while (head != nullptr)
			PopFront();
	}

	void PushFront(T value)
	{
		if (head == nullptr)
		{
			head = new Node<T>(value, nullptr, nullptr);
			tail = head;
		}
		else
		{
			Node<T>* newNode = new Node<T>(value, head, nullptr);
			head->previous = newNode;
			head = newNode;
		}
		++size;
	}

	void PopFront()
	{
		if (head == nullptr)
			return;
		else if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			head = head->next;
			delete head->previous;
			head->previous = nullptr;
		}
		--size;
	}

	void PushBack()
	{
		if (tail == nullptr)
		{
			tail = new Node<T>(value, nullptr, nullptr);
			head = tail;
		}
		else
		{
			Node<T>* newNode = new Node<T>(value, nullptr, tail);
			tail->next = newNode;
			tail = newNode;
		}
		++size;
	}

	void PopBack()
	{
		if (tail == nullptr)
			return;
		else if (tail == head)
		{
			delete tail;
			tail = nullptr;
			head = nullptr;
		}
		else
		{
			tail = tail->previous;
			delete tail->next;
			tail->next = nullptr;
		}
		--size;
	}

	void Remove(const T& value)
	{
		if (head == nullptr)
			return;
		else
		{
			Node<T>* node = head;
			while (node != nullptr)
			{
				if (node->data == value)
				{
					Remove(node);
					return;
				}
				node = node->next;
			}
		}
	}

	void Remove(Node* node)
	{
		if (node == nullptr)
			return;
		else if (head == tail || node == tail)
			PopBack();
		else if (node == head)
			PopFront();
		else
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
			delete node;
			--size;
		}
	}

	void Insert(Node* node, T value)
	{
		if (node == nullptr)
			return;
		else if (head == tail || node == tail)
			PushBack(value);
		else
		{
			Node<T>* newNode = new Node<T>(value, node->next, node);
			node->next = newNode;
			newNode->next->previous = newNode;
			++size;
		}
	}

	void Clear()
	{
		while (head != nullptr)
			PopFront();
		size = 0;
	}

	Node* Begin() const
	{
		return head;
	}

	Node* End() const
	{
		return new Node<T>(nullptr, tail);
	}

	T& First() const
	{
		return *this[0];
	}

	T& Last() const
	{
		return *this[size - 1];
	}
};
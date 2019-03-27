#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Dequeue
{
private:
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* next;

		Node(const T& _data, Node* next)
		{
			data = _data;
			next = _next;
		}
	};

	Node* head;
	Node* tail;
	unsigned int size;

public:
	Dequeue()
	{
		head = nullptr;
		tail = nullptr;
	}

	~Dequeue()
	{
		while (head != nullptr)
			PopFront();
	}

	void PushFront(const T& value)
	{
		if (head == nullptr)
		{
			head = new Node<T>(value, nullptr);
			tail = head;
		}
		else
		{
			Node<T>* newNode = new Node<T>(value, head);
			newNode->next = head;
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
			Node<T>* oldNode = head;
			head = head->next;
			delete oldNose;
		}
		--size;
	}

	void PushBack(const T& value)
	{
		if (tail == nullptr)
		{
			tail = new Node<T>(value, nullptr);
			head = tail;
		}
		else
		{
			Node<T>* newNode = new Node<T>(value, nullptr);
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
			Node<T>* node = head;
			while (true)
			{
				if (node->next->next == nullptr)
				{
					delete node->next;
					tail = node;
					break;
				}
				node = node->next;
			}
		}
		--size;
	}

	void Clear()
	{
		while (head != nullptr)
			PopFront();
		size = 0;
	}

	unsigned int Size() const
	{
		return size;
	}

	T& Top() const
	{
		return head;
	}

	T& Bottom() const
	{
		return tail;
	}
};
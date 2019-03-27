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
			PopBack();
	}

	void PushFront(const T& value)
	{

	}

	void PopFront()
	{

	}

	void PushBack(const T& value)
	{

	}

	void PopBack()
	{

	}

	void Clear()
	{
		while (head != nullptr)
			PopBack();
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
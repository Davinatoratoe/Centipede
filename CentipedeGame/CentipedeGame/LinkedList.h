#pragma once
#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
private:
	template <typename T>
	class LinkedListNode
	{
	public:
		T data;
		LinkedListNode* next;
		LinkedListNode* previous;

		LinkedListNode(LinkedListNode* _next, LinkedListNode* _previous)
		{
			_next = next;
			_previous = previous;
		}
		
		LinkedListNode(const T& _data, LinkedListNode* _next, LinkedListNode* _previous)
		{
			data = _data;
			next = _next;
			previous = _previous;
		}
	};

	LinkedListNode<T>* head;
	LinkedListNode<T>* tail;
	unsigned int size;

public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	
	LinkedList(const LinkedList<T>& copy)
	{
		head = nullptr;
		tail = nullptr;
		size = 0;

		LinkedListNode<T>* node = copy.head;
		while (node != nullptr)
		{
			PushBack(node->data);
			node = node->next;
		}
	}

	~LinkedList()
	{
		while (head != nullptr)
			PopFront();
	}
	
	void PushFront(const T& value)
	{
		if (head == nullptr)
		{
			head = new LinkedListNode<T>(value, nullptr, nullptr);
			tail = head;
		}
		else
		{
			LinkedListNode<T>* newNode = new LinkedListNode<T>(value, head, nullptr);
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

	void PushBack(const T& value)
	{
		if (tail == nullptr)
		{
			tail = new LinkedListNode<T>(value, nullptr, nullptr);
			head = tail;
		}
		else
		{
			LinkedListNode<T>* newNode = new LinkedListNode<T>(value, nullptr, tail);
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
		else if (head->data == value)
			PopFront();
		else if (tail->data == value)
			PopBack();
		else
		{
			LinkedListNode<T>* node = head;
			while (node != nullptr)
			{
				if (node->data == value)
				{
					node->previous->next = node->next;
					node->next->previous = node->previous;
					delete node;
					--size;
					return;
				}
				node = node->next;
			}
		}
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

	T& First() const
	{
		if (head != nullptr)
			return head.data;
	}

	T& Last() const
	{
		if (tail != nullptr)
			return tail.data;
	}

	LinkedList<T>& operator= (const LinkedList<T>& other)
	{
		Clear();
		LinkedListNode<T>* node = other.head;
		while (node != nullptr)
		{
			PushBack(node->data);
			node = node->next;
		}
		return *this;
	}

	friend ostream& operator<< (ostream& os, const LinkedList<T>& list)
	{
		os << "[";
		os << "Not implemented";
		/*
		LinkedListNode<T>* node = list.head;
		while (node != nullptr)
		{
			if (node != head)
				os << ", ";
			os = node.data;
			node = node->next;
		}
		*/
		os << "]";
		return os;
	}

	void PrintDetails()
	{
		cout << "Size: " << size << "   ";

		LinkedListNode<T>* node = head;
		while (node != nullptr)
		{
			cout << (node->data);
			cout << " ";
			node = node->next;
		}
		cout << endl;
	}
};
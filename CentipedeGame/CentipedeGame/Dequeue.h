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

		Node(const T& _data, Node* _next)
		{
			data = _data;
			next = _next;
		}
	};

	Node<T>* head;
	Node<T>* tail;
	unsigned int size;

public:
	Dequeue()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	Dequeue(const Dequeue<T>& copy)
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
		Node<T>* node = copy.head;
		while (node != nullptr)
		{
			PushBack(node->data);
			node = node->next;
		}
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
			head = oldNode->next;
			delete oldNode;
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
			while (node->next->next != nullptr)
				node = node->next;
			delete node->next;
			tail = node;
			tail->next = nullptr;
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

	Dequeue<T>& operator= (const Dequeue<T>& other)
	{
		Clear();
		Node<T>* node = other.head;
		while (node != nullptr)
		{
			PushBack(node->data);
			node = node->next;
		}
		return *this;
	}

	friend ostream& operator<< (ostream& os, const Dequeue<T>& dequeue)
	{
		os << "[";
		os << "Not implemented";
		os << "]";
		return os;
	}

	void PrintDetails() const
	{
		cout << "Size: " << size << "  ";
		Node<T>* node = head;
		while (node != nullptr)
		{
			cout << node->data;
			cout << " ";
			node = node->next;
		}
		cout << endl;
	}
};
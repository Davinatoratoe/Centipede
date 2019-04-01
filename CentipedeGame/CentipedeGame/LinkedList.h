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
	//https://codereview.stackexchange.com/questions/74609/custom-iterator-for-a-linked-list-class
	template <typename T>
	class LinkedListIterator
	{
	private:
		LinkedListNode<T>* node;

	public:
		LinkedListIterator() 
		{
			node = nullptr;
		}
		
		LinkedListIterator(LinkedListNode<T>* _node)
		{
			node = _node;
		}

		bool operator== (const LinkedListIterator<T>& other) const
		{
			return node == other.node;
		}

		bool operator!= (const LinkedListIterator<T>& other) const
		{
			return node != other.node;
		}
		
		LinkedListIterator& operator++ ()
		{
			if (node != nullptr)
			{
				node = node->next;
				return *this;
			}
		}

		LinkedListIterator& operator-- ()
		{
			if (node != nullptr)
			{
				node = node->previous;
				return *this;
			}
		}

		T& operator* () const
		{
			if (node != nullptr)
				return node->data;
		}

		T& operator-> () const
		{
			if (node != nullptr)
				return node->data;
		}
	};

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

	LinkedListIterator<T> Begin() const
	{
		return LinkedListIterator<T>(head);
	}

	LinkedListIterator<T> End() const
	{
		return LinkedListIterator<T>(tail);
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
		for (auto i = list.Begin(); i != list.End(); ++i)
		{
			if (i != list.Begin())
				cout << ", ";
			cout << *i;
		}
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
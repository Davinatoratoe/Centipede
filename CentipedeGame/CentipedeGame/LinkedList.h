#pragma once
#include <iostream>
#include <sstream>

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
	LinkedListNode<T>* end;
	unsigned int size;

	void Remove(LinkedListNode<T>* node)
	{
		if (node == head)
			PopFront();
		else if (node == tail)
			PopBack();
		else
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
			delete node;
			--size;
		}
	}

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
			return node != nullptr && other.node != nullptr && node == other.node;
		}

		bool operator!= (const LinkedListIterator<T>& other) const
		{
			return node == nullptr || other.node == nullptr || node != other.node;
		}
		
		LinkedListIterator& operator++ ()
		{
			if (node != nullptr)
				node = node->next;
			return *this;
		}

		LinkedListIterator& operator-- ()
		{
			if (node != nullptr)
				node = node->previous;
			return *this;
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
		head = new LinkedListNode<T>(nullptr, nullptr);
		tail = head;
		end = new LinkedListNode<T>(nullptr, tail);
		head->next = end;
		size = 0;
	}
	
	LinkedList(const LinkedList<T>& copy)
	{
		head = new LinkedListNode<T>(nullptr, nullptr);
		tail = head;
		end = new LinkedListNode<T>(nullptr, tail);
		head->next = end;
		size = 0;

		for (auto i = copy.Begin(); i != copy.End(); ++i)
			PushBack(*i);
	}

	~LinkedList()
	{
		while (size > 0)
			PopFront();
		delete end;
		delete head;
	}
	
	void PushFront(const T& value)
	{
		if (size == 0)
			head->data = value;
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
		if (size == 0)
			return;
		else if (size == 1)
		{
			head->next = end;
			tail = head;
			end->previous = tail;
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
		if (size == 0)
			tail->data = value;
		else
		{
			LinkedListNode<T>* newNode = new LinkedListNode<T>(value, nullptr, tail);
			tail->next = newNode;
			tail = newNode;
			tail->next = end;
		}
		end->previous = tail;
		++size;
	}

	void PopBack()
	{
		if (size == 0)
			return;
		else if (size == 1)
		{
			head->next = end;
			tail = head;
			end->previous = tail;
		}
		else if (size > 1)
		{
			tail = tail->previous;
			delete tail->next;
			tail->next = end;
			end->previous = tail;
		}
		--size;
	}

	void Remove(const T& value)
	{
		if (size == 0)
			return;
		else
		{
			LinkedListNode<T>* node = head;
			LinkedList<LinkedListNode<T>*> toRemove = LinkedList<LinkedListNode<T>*>();
			while (node != end)
			{
				if (node->data == value)
					toRemove.PushBack(node);
				node = node->next;
			}

			while (toRemove.Size() > 0)
			{
				Remove(toRemove.Last());
				toRemove.PopBack();
			}
		}
	}

	void Clear()
	{
		while (size > 0)
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
			return head->data;
	}

	T& Last() const
	{
		if (tail != nullptr)
			return tail->data;
	}

	LinkedListIterator<T> Begin() const
	{
		return LinkedListIterator<T>(head);
	}

	LinkedListIterator<T> End() const
	{
		if (size == 0)
			return Begin();
		return LinkedListIterator<T>(end);
	}

	LinkedList<T>& operator= (const LinkedList<T>& other)
	{
		Clear();
		for (auto i = other.Begin(); i != other.End(); ++i)
			PushBack(*i);
		return *this;
	}

	friend ostream& operator<< (ostream& os, const LinkedList<T>& list)
	{
		os << "[";
		for (auto i = list.Begin(); i != list.End(); ++i)
		{
			if (i != list.Begin())
				os << ", ";
			os << *i;
		}
		os << "]";
		return os;
	}

	void PrintDetails()
	{
		cout << "Size: " << size << "   ";
		for (auto i = Begin(); i != End(); ++i)
		{
			cout << *i;
			cout << " ";
		}
		cout << endl;
	}

	/// <summary>
	/// Get the list represented as a string.
	/// </summary>
	/// <returns>A string representation of the list.</returns>
	string ToString() const
	{
		ostringstream stream;
		stream << *this;
		return stream.str();
	}
};
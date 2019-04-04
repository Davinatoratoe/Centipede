/*
	File: LinkedList.h
	Contains: LinkedList, LinkedListNode, LinkedListIterator
*/

#pragma once
#include <iostream>
#include <sstream>

using namespace std;

/// <summary>
/// The Linked List is a container that links elements (nodes) together using pointers.
/// This is a Doubly-Linked List because each node containers a pointer to the next node and previous node.
/// The class also implements a custom iterator to allow traversing the list.
/// </summary>
template <typename T>
class LinkedList
{
private:
	/// <summary>
	/// The Linked List Node contains the data and a pointer to the next & previous node.
	/// </summary>
	template <typename T>
	class LinkedListNode
	{
	public:
		T data;						//The data in the node
		LinkedListNode* next;		//A pointer to the next node
		LinkedListNode* previous;	//A pointer to the previous node

		/// <summary>
		/// Overloaded constructor.
		/// </summary>
		/// <param name="_next">A pointer to the next node/</param>
		/// <param name="_previous">A pointer to the previous node.</param>
		LinkedListNode(LinkedListNode* _next, LinkedListNode* _previous)
		{
			_next = next;
			_previous = previous;
		}
		
		/// <summary>
		/// Overloaded constructor.
		/// </summary>
		/// <param name="_data">The data to store in the node.</param>
		/// <param name="_next">A pointer to the next node.</param>
		/// <param name="_previous">A pointer to the previous node.</param>
		LinkedListNode(const T& _data, LinkedListNode* _next, LinkedListNode* _previous)
		{
			data = _data;
			next = _next;
			previous = _previous;
		}
	};

	LinkedListNode<T>* head;	//The head of the linked list (first node)
	LinkedListNode<T>* tail;	//The tail of the linked list (last node)
	LinkedListNode<T>* end;		//One past the tail used for iterating through the linked list
	unsigned int size;			//The number of nodes in the linked list

	/// <summary>
	/// A function that removes a specific node from the linked list.
	/// This is private because the linked list node class is also private.
	/// </summary>
	/// <param name="node"></param>
	void Remove(LinkedListNode<T>* node)
	{
		if (node == head)		//If we are removing the head, then pop the front node
			PopFront();
		else if (node == tail)	//If we are removing the tail, then pop the back node
			PopBack();
		else
		{
			//Otherwise delete the node and readjust the pointers
			node->previous->next = node->next;
			node->next->previous = node->previous;
			delete node;
			--size;
		}
	}

public:
	/// <summary>
	/// The Linked List Iterator class allows iterating through a linked list.
	/// Implementation helped by https://codereview.stackexchange.com/questions/74609/custom-iterator-for-a-linked-list-class
	/// </summary>
	template <typename T>
	class LinkedListIterator
	{
	private:
		LinkedListNode<T>* node;	//The node that this iterator is pointing to

	public:
		/// <summary>
		/// Overloaded constructor.
		/// </summary>
		/// <param name="_node">A pointer to to node that this iterator should point to.</param>
		LinkedListIterator(LinkedListNode<T>* _node)
		{
			node = _node;
		}

		/// <summary>
		/// == operator overload.
		/// Checks if this iterator is equal to another by testing if the node pointers are equal.
		/// I.e. two iterators with the same node are the same iterator.
		/// </summary>
		/// <param name="other">The other iterator to check against.</param>
		/// <returns>True if the two iterators are equal.</returns>
		bool operator== (const LinkedListIterator<T>& other) const
		{
			return node != nullptr && other.node != nullptr && node == other.node;
		}

		/// <summary>
		/// != operator overload.
		/// Checks if this iterator is not equal to another by testing if the node pointers are different.
		/// </summary>
		/// <param name="other">The other iterator to check against.</param>
		/// <returns>True if the two iterators are not equal.</returns>
		bool operator!= (const LinkedListIterator<T>& other) const
		{
			return !(*this == other);
		}

		/// <summary>
		/// ++i operator overload.
		/// Will move this iterator to point to the next node.
		/// </summary>
		/// <returns>This iterator representing the next node.</returns>
		LinkedListIterator& operator++ ()
		{
			if (node != nullptr)
				node = node->next;
			return *this;
		}

		/// <summary>
		/// --i operator overload.
		/// Will move this iterator to point to the previous node.
		/// </summary>
		/// <returns>This iterator representing the previous node.</returns>
		LinkedListIterator& operator-- ()
		{
			if (node != nullptr)
				node = node->previous;
			return *this;
		}

		/// <summary>
		/// * de-reference operator overload.
		/// Will return the data within the node.
		/// </summary>
		/// <returns>The data of the node that the iterator is representing.</returns>
		T& operator* () const
		{
			if (node != nullptr)
				return node->data;
		}

		/// <summary>
		/// -> arrow operator overload.
		/// Will return the data within the node.
		/// </summary>
		/// <returns>The data of the node that the iterator is representing.</returns>
		T& operator-> () const
		{
			if (node != nullptr)
				return node->data;
		}
	};

	/// <summary>
	/// Default constructor.
	/// </summary>
	LinkedList()
	{
		//Set all the values to their initial state
		head = new LinkedListNode<T>(nullptr, nullptr);
		tail = head;
		end = new LinkedListNode<T>(nullptr, tail);
		head->next = end;
		size = 0;
	}
	
	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="copy">The list we are copying.</param>
	LinkedList(const LinkedList<T>& copy)
	{
		//Set all the values to their initial state
		head = new LinkedListNode<T>(nullptr, nullptr);
		tail = head;
		end = new LinkedListNode<T>(nullptr, tail);
		head->next = end;
		size = 0;

		//Iterate through the copy and push its data into this list
		for (auto i = copy.Begin(); i != copy.End(); ++i)
			PushBack(*i);
	}

	/// <summary>
	/// Deconstructor.
	/// </summary>
	~LinkedList()
	{
		//Pop the nodes until none remain
		while (size > 0)
			PopFront();

		//Delete remaining pointers
		delete end;
		delete head;
	}
	
	/// <summary>
	/// Push a value to the front of the linked list.
	/// </summary>
	/// <param name="value">The value to push.</param>
	void PushFront(const T& value)
	{
		if (size == 0)	//If there are no nodes, set the data on the head
			head->data = value;
		else
		{
			//Create a new node and readjust the head pointer
			LinkedListNode<T>* newNode = new LinkedListNode<T>(value, head, nullptr);
			head->previous = newNode;
			head = newNode;
		}
		++size;
	}

	/// <summary>
	/// Pop a value off the front of the linked list.
	/// </summary>
	void PopFront()
	{
		if (size == 0)	//If there are no nodes, just return
			return;
		else if (size == 1)	//If there is only one node...
		{
			//Set the node after the head to the end node and point to the tail to the head
			head->next = end;
			tail = head;
			end->previous = tail;
		}
		else
		{
			//Delete the head and readjust the pointers
			head = head->next;
			delete head->previous;
			head->previous = nullptr;
		}
		--size;
	}

	/// <summary>
	/// Push a value to the end of the linked list.
	/// </summary>
	/// <param name="value">The value to push.</param>
	void PushBack(const T& value)
	{
		if (size == 0)	//If there are no nodes, set the data on the tail
			tail->data = value;
		else
		{
			//Create a new node and readjust the tail pointer and the end pointer
			LinkedListNode<T>* newNode = new LinkedListNode<T>(value, nullptr, tail);
			tail->next = newNode;
			tail = newNode;
			tail->next = end;
		}
		end->previous = tail;
		++size;
	}

	/// <summary>
	/// Pop a value off the back of the linked list.
	/// </summary>
	void PopBack()
	{
		if (size == 0)	//If there are no nodes, just return
			return;
		else if (size == 1)	//If there is only one node...
		{
			//Set the node after the head to the end node and point to the tail to the head
			head->next = end;
			tail = head;
			end->previous = tail;
		}
		else
		{
			//Delete the tail and readjust the pointers, and set the end pointer
			tail = tail->previous;
			delete tail->next;
			tail->next = end;
			end->previous = tail;
		}
		--size;
	}

	/// <summary>
	/// Remove all occurrences of a specific value from the linked list.
	/// </summary>
	/// <param name="value">The value to remove from the linked list.</param>
	void Remove(const T& value)
	{
		if (size == 0)	//If there are no nodes then return
			return;
		else
		{
			//Loop through the nodes in the linked list and push the ones to be removed to another linked list
			LinkedListNode<T>* node = head;
			LinkedList<LinkedListNode<T>*> toRemove = LinkedList<LinkedListNode<T>*>();
			while (node != end)
			{
				//If the data matches the value to remove add it to the list of nodes to be removed
				if (node->data == value)
					toRemove.PushBack(node);
				node = node->next;
			}

			//Loop through the nodes in the list of nodes to remove, removing the nodes one by one
			while (toRemove.Size() > 0)
			{
				Remove(toRemove.Last());
				toRemove.PopBack();
			}
		}
	}

	/// <summary>
	/// Clear all values from the linked list.
	/// </summary>
	void Clear()
	{
		//Pop the front node until there are no more nodes
		while (size > 0)
			PopFront();
	}

	/// <summary>
	/// Getter for the size of the linked list.
	/// </summary>
	/// <returns>The number of nodes in the linked list.</returns>
	unsigned int Size() const
	{
		return size;
	}

	/// <summary>
	/// Getter for the first value in the linked list.
	/// </summary>
	/// <returns>The first value in the linked list.</returns>
	T& First() const
	{
		if (head != nullptr)
			return head->data;
	}

	/// <summary>
	/// Getter for the last value in the linked list.
	/// </summary>
	/// <returns>The last value in the linked list.</returns>
	T& Last() const
	{
		if (tail != nullptr)
			return tail->data;
	}

	/// <summary>
	/// A getter for an iterator pointing to the beginning of the linked list.
	/// </summary>
	/// <returns>An iterator at the start of the linked list.</returns>
	LinkedListIterator<T> Begin() const
	{
		return LinkedListIterator<T>(head);
	}

	/// <summary>
	/// A getter for an iterator pointing to the end of the linked list.
	/// </summary>
	/// <returns>An iterator at the end of the linked list.</returns>
	LinkedListIterator<T> End() const
	{
		if (size == 0)
			return Begin();
		return LinkedListIterator<T>(end);	//Use end to represent an iterator one past the tail
	}

	/// <summary>
	/// Assignment operator overload.
	/// Assigns this list the values of another list.
	/// </summary>
	/// <param name="other">The list to copy the values from.</param>
	/// <returns>This linked list with the values from the other linked list.</returns>
	LinkedList<T>& operator= (const LinkedList<T>& other)
	{
		//Clear this linked list first to clean up memory
		Clear();
		//Loop through the other linked list and push the values into our linked list
		for (auto i = other.Begin(); i != other.End(); ++i)
			PushBack(*i);
		return *this;
	}

	/// <summary>
	/// << operator overload.
	/// Allows displaying the linked list to an output stream.	
	/// </summary>
	/// <param name="os">The output stream to display to.</param>
	/// <param name="list">The linked list to display.</param>
	/// <returns>The output stream with the linked list displayed to it.</returns>
	friend ostream& operator<< (ostream& os, const LinkedList<T>& list)
	{
		os << "[";
		//Iterate through the linked list and output the data to the output stream
		for (auto i = list.Begin(); i != list.End(); ++i)
		{
			if (i != list.Begin())
				os << ", ";
			os << *i;
		}
		os << "]";
		return os;
	}

	/// <summary>
	/// Print details about the linked list to std::cout.
	/// </summary>
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
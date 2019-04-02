/*
	File: DynamicList.h
	Contains: List
*/

#pragma once
#include <iostream>
#include <sstream>

using namespace std;

/// <summary>
/// The List class is a Dynamic List container that expands in memory when needed.
/// </summary>
template <typename T>
class List
{
private:
	T* data;				//A pointer to the start of the array in the heap
	unsigned int size;		//The size of the list
	unsigned int capacity;	//The current capacity of the list
	const unsigned int MAX_CAPACITY = 500;	//The maximum capacity allowed to be reserved for the list

public:
	/// <summary>
	/// Default constructor.
	/// Has an initial capacity of 5.
	/// </summary>
	List()
	{
		capacity = 5;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}
	
	/// <summary>
	/// Overloaded constructor.
	/// </summary>
	/// <param name="_capacity">The initial capacity of this list.</param>
	List(unsigned int _capacity)
	{
		capacity = _capacity;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}
	
	/// <summary>
	/// Copy constructor.
	/// Copies the data from the copy to this list.
	/// </summary>
	/// <param name="copy">The copy.</param>
	List(const List& copy)
	{
		capacity = copy.capacity;
		size = copy.size;
		data = new T[capacity];
		memcpy(data, copy.data, sizeof(T) * capacity);
	}

	/// <summary>
	/// Deconstructor.
	/// </summary>
	~List()
	{
		delete data;
	}

	/// <summary>
	/// Increase the capacity of the list by a certain amount.
	/// </summary>
	/// <param name="amount">The amount to increase the capacity by.</param>
	void Reserve(unsigned int amount)
	{
		if (capacity == MAX_CAPACITY)					//If the capacity is at the maximum capacity, then return
			return;
		else if (capacity + amount > MAX_CAPACITY)		//If the new capacity will be greater than the maximum capacity, handle accordingly
		{
			T* newData = new T[MAX_CAPACITY];
			memcpy(newData, data, sizeof(T) * MAX_CAPACITY);
			delete data;
			data = newData;
			capacity = MAX_CAPACITY;
		}	
		else	//Otherwise handle like normal
		{
			T* newData = new T[capacity + amount];
			memcpy(newData, data, sizeof(T) * capacity);
			delete data;
			data = newData;
			capacity += amount;
		}
	}

	/// <summary>
	/// Push a new value to the list.
	/// If it will not fit then increase the capacity.
	/// </summary>
	/// <param name="value">The value to push to the list.</param>
	void Push(const T& value)
	{
		if (size == capacity)		//If there is no more capacity then double the capacity
			Reserve(capacity * 2);
		if (size != capacity)		//If there is more capacity now, then add the value
		{
			data[size] = value;
			++size;
		}
	}

	/// <summary>
	/// Pop the element off the end of the list.
	/// </summary>
	void Pop()
	{
		if (size > 0)
			--size;
	}

	/// <summary>
	/// Clear the list.
	/// </summary>
	void Clear()
	{
		size = 0;
	}

	/// <summary>
	/// Getter for the size of the list.
	/// </summary>
	/// <returns>The number of elements in the list.</returns>
	unsigned int Size() const
	{
		return size;
	}

	/// <summary>
	/// Getter for the current capacity of the list.
	/// </summary>
	/// <returns>The current capacity of the list.</returns>
	unsigned int Capacity() const
	{
		return capacity;
	}

	/// <summary>
	/// Getter for the maximum possible capacity for any list.
	/// </summary>
	/// <returns>The maximum possible capacity for any list.</returns>
	const unsigned int MaxCapacity() const
	{
		return MAX_CAPACITY;
	}

	/// <summary>
	/// Assignment operator overload.
	/// </summary>
	/// <param name="other">The other list to copy data from.</param>
	/// <returns>This list with copied data.</returns>
	List& operator= (const List& other)
	{
		delete data;
		capacity = other.capacity;
		size = other.size;
		data = new T[capacity];
		memcpy(data, other.data, sizeof(T) * capacity);
		return *this;
	}

	/// <summary>
	/// << operator overload.
	/// Allows displaying the list to an ostream.
	/// </summary>
	/// <param name="os">The ostream to display the list to.</param>
	/// <param name="list">The list to display,</param>
	/// <returns>The ostream with the list displayed.</returns>
	friend ostream& operator<< (ostream& os, const List<T>& list)
	{
		os << "[";
		for (unsigned int i = 0; i < list.Size(); ++i)
		{
			if (i != 0)
				os << ", ";
			os << list[i];
		}
		os << "]";
		return os;
	}

	/// <summary>
	/// [] sub-script operator overload.
	/// Allow accessing the list using square brackets.
	/// </summary>
	/// <param name="index">The index to access.</param>
	/// <returns>The element at the specified index.</returns>
	T& operator[] (unsigned int index) const
	{
		if (index >= 0 && index < size)
			return data[index];
	}

	/// <summary>
	/// Print details about this list to std::cout.
	/// </summary>
	void PrintDetails() const
	{
		cout << "Size: " << size << "   ";
		cout << "Capacity: " << capacity << "   ";
		for (unsigned int i = 0; i < size; ++i)
			cout << data[i] << " ";
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
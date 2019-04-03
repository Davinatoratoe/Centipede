#pragma once
#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
class Stack
{
private:
	T* data;
	unsigned int size;
	unsigned int capacity;

public:
	Stack()
	{
		capacity = 10;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	Stack(const Stack<T>& copy)
	{
		capacity = copy.capacity;
		size = copy.size;
		data = new T[capacity];
		memcpy(data, copy.data, sizeof(T) * capacity);
	}

	Stack(unsigned int _capacity)
	{
		capacity = _capacity;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	~Stack()
	{
		delete data;
	}

	void Push(const T& value)
	{
		if (size < capacity)
		{
			data[size] = value;
			++size;
		}
	}

	void Pop()
	{
		if (size > 0)
			--size;
	}

	void Clear()
	{
		size = 0;
	}

	unsigned int Size() const
	{
		return size;
	}

	unsigned int Capacity() const
	{
		return capacity;
	}

	bool Empty() const
	{
		return size == 0;
	}

	T& Top() const
	{
		if (size > 0)
			return data[size - 1];
	}

	Stack<T>& operator= (const Stack<T>& other)
	{
		delete data;
		capacity = other.capacity;
		size = other.size;
		data = new T[capacity];
		memcpy(data, other.data, sizeof(T) * capacity);
		return *this;
	}

	friend ostream& operator<< (ostream& os, const Stack<T>& stack)
	{
		if (!stack.Empty())
			os << stack.Top();
		else
			os << "Empty";
		return os;
	}

	void PrintDetails() const
	{
		cout << "Size: " << size << "   ";
		cout << "Capacity: " << capacity << "   ";
		if (!Empty())
			cout << Top();
		else
			cout << "Empty";
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
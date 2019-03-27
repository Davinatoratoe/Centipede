#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Stack
{
private:
	T* data;
	unsigned int size;
	unsigned int capacity;

public:
	public Stack()
	{
		capacity = 10;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	public Stack(unsigned int _capacity)
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

	T& Top() const
	{
		if (size > 0)
			return data[size - 1];
	}
};
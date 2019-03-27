#pragma once
#include <iostream>

using namespace std;

template <typename T>
class List
{
private:
	T* data;
	unsigned int size;
	unsigned int capacity;

public:
	List()
	{
		capacity = 5;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}
	
	List(unsigned int _capacity)
	{
		capacity = _capacity;
		size = 0;
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}
	
	List(const List& copy)
	{
		capacity = copy.capacity;
		size = copy.size;
		data = new T[capacity];
		memcpy(data, copy.data, sizeof(T) * capacity);
	}

	~List()
	{
		delete data;
	}

	void Reserve(unsigned int amount)
	{
		T* newData = new T[capacity + amount];
		memcpy(newData, data, capacity);
		delete data;
		data = newData;
		capacity += amount;
	}

	void Push(const T& value)
	{
		if (size == capacity)
			Reserve(capacity * 2);
		data[size] = value;
		++size;
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

	List& operator= (const List& other)
	{
		delete data;
		capacity = other.capacity;
		size = other.size;
		data = new T[capacity];
		memcpy(data, other.data, sizeof(T) * capacity);
	}

	T& operator[] (unsigned int index) const
	{
		if (index >= 0 && index < size)
			return data[index];
	}
};
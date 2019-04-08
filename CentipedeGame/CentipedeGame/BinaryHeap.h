#pragma once

template <typename T>
class Heap
{
private:
	T* data;
	unsigned int size;
	unsigned int arraySize;

public:
	Heap()
	{
		data = new T[1];
	}

	/// <summary>
	/// Deconstructor.
	/// </summary>
	~Heap()
	{
		delete[] data;
	}

	/// <summary>
	/// Adds a new value to the heap.
	/// </summary>
	/// <param name="value">The value to add to the heap.</param>
	void Push(const T& value)
	{

	}

	/// <summary>
	/// Remove the root element from the tree.
	/// </summary>
	void Pop()
	{

	}

	/// <summary>
	/// Removes a value from the heap.
	/// </summary>
	/// <param name="value">The value to remove from the heap.</param>
	void Remove(const T& value)
	{

	}

	/// <summary>
	/// Removes all values from the tree.
	/// </summary>
	void Clear()
	{

	}

	/// <summary>
	/// Get the value of the root element of the tree.
	/// </summary>
	/// <returns>The value of the root element of the tree.</returns>
	T& Peek() const
	{
		if (size > 0)
			return data[0];
	}

	/// <summary>
	/// Get the size of the tree.
	/// </summary>
	/// <returns>The number of nodes in the tree.</returns>
	unsigned int Size() const
	{
		return size;
	}

	/// <summary>
	/// Get a value from the heap.
	/// </summary>
	/// <param name="index">The index of the value.</param>
	/// <returns>The value.</returns>
	T& operator[] (unsigned int index) const
	{
		if (index >= 0 && index < arraySize)
			return data[index];
	}
};
#pragma once
#include <iostream>
#include <math.h>

using namespace std;

template <typename T>
class Heap
{
private:
	T* data;				//Array
	unsigned int size;		//Size of the heap
	const unsigned int MAX_SIZE = 100;

	int GetParent(unsigned int index)
	{
		if (index == 0)
			return -1;
		return (int)floor((index - 1) / 2);
	}

	int GetFirstChild(unsigned int index)
	{
		int result = (2 * index) + 1;
		if (result > size)
			return -1;
		return result;
	}

	int GetSecondChild(unsigned int index)
	{
		int result = (2 * index) + 2;
		if (result > size)
			return -1;
		return result;
	}

	void Swap(T* a, T* b)
	{
		T temp = *a;
		*a = *b;
		*b = temp;
	}

	/// <summary>
	/// Recursively prints the tree to std::cout
	/// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
	/// </summary>
	/// <param name="index">The index to process. (Initially 0)</param>
	/// <param name="space">The space between the levels. (Initially 0)</param>
	void PrintTree(unsigned int index, int space) const
	{
		//Exit if the index isn't valid
		if (index == -1)
			return;

		//Increase the distance between the levels
		space += 5;

		//Process the right child
		PrintTree(GetSecondChild(index), space);

		//Print the current node
		cout << endl;
		for (int i = 5; i < space; ++i)
			cout << " ";
		cout << data[index] << endl;

		//Process the left child
		PrintTree(GetFirstChild(index), space);
	}

public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	Heap()
	{
		size = 0;
		data = new T[MAX_SIZE];
		memset(data, 0, sizeof(T) * MAX_SIZE);
	}

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="copy"></param>
	Heap(const Heap& copy)
	{
		size = copy.size;
		data = new T[MAX_SIZE];
		memcpy(data, copy.data, sizeof(T) * MAX_SIZE);
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
		//Exit if the heap cannot fit another value
		if (size == MAX_SIZE)
			return;

		//Add the value to the end of the heap
		data[size] = value;
		++size;

		//Exit if this was the first value added
		if (size == 1)
			return;

		//Get the current index of this value
		unsigned int index = size - 1;				

		//Get the index of the parent of this value
		unsigned int parentIndex = GetParent(index);

		//Swap the value with its parent if the parent is smaller than the value
		//Repeat until there are no more swaps required
		while (index > 0 && data[parentIndex] < data[index])
		{
			//Swap the value and its parent
			Swap(data[parentIndex], data[index]);

			//Set the index to the parent's index
			index = parentIndex;

			//Find the new indexes' parent index
			parentIndex = GetParent(index);
		}
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
		if (index >= 0 && index < size)
			return data[index];
	}

	/// <summary>
	/// Assignment operator overload.
	/// </summary>
	/// <param name="other">The other heap to assign to this one.</param>
	/// <returns>This heap with the values of the other heap.</returns>
	Heap& operator= (const Heap& other)
	{
		delete[] data;
		size = other.size;
		data = new T[MAX_SIZE];
		memcpy(data, other.data, sizeof(T) * MAX_SIZE);
		return *this;
	}

	/// <summary>
	/// Print details about the tree.
	/// </summary>
	void PrintDetails() const
	{
		cout << "Size: " << size << endl;
		if (size > 0)
		{
			//Call a function to recursively print the heap to std::cout
			PrintTree(0, 0);
		}
		else
			cout << "Empty" << endl;
		cout << endl;
	}
};
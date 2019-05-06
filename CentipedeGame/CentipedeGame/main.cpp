#include <iostream>
#include "CentipedeGameApp.h"
#include "BinaryTree.h"
#include "DynamicList.h"
#include "Dequeue.h"
#include "LinkedList.h"
#include "Stack.h"
#include "BinaryHeap.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

/// <summary>
/// Print the given tree node.
/// </summary>
/// <param name="node">The node to print.</param>
template <typename T>
void PrintNode(BinaryTreeNode<T>* node)
{
	cout << node->data << " ";
}

/// <summary>
/// Test the Binary Tree.
/// </summary>
void TestBinaryTree()
{
	cout << "---Testing Binary Tree" << endl;

	BinaryTree<int> tree;
	tree.Insert(50);
	tree.Insert(75);
	tree.Insert(60);
	tree.Insert(100);
	tree.Insert(25);
	tree.Insert(30);
	tree.Insert(5);
	tree.PrintDetails();

	tree.Remove(5);		//Remove a leaf
	tree.Remove(25);	//Remove a node with one branch
	tree.Remove(5);		//Remove a non-existent node
	tree.Remove(50);	//Remove a node with two branches (root)
	tree.PrintDetails();

	tree.Clear();		//Empty the tree
	tree.PrintDetails();
	
	tree.Insert(50);
	tree.Insert(75);
	tree.Insert(60);
	tree.Insert(100);
	tree.Insert(25);
	tree.Insert(30);
	tree.Insert(5);
	cout << "Find node 25: " << tree.Find(25)->data << endl;	//Find a node
	cout << "Find non-existent node 10: " << ((tree.Find(10) == nullptr) ? "Not found" : "Found?") << endl;	//Find a non-existent node
	
	cout << endl << "Depth First Pre-Order Search: ";
	tree.DepthFirstSearch(SEARCH_PRE_ORDER, PrintNode);		//Perform a depth first pre order search
	cout << endl << "Depth First In-Order Search: ";
	tree.DepthFirstSearch(SEARCH_IN_ORDER, PrintNode);		//Perform a depth first in order search
	cout << endl << "Depth First Post-Order Search: ";
	tree.DepthFirstSearch(SEARCH_POST_ORDER, PrintNode);	//Perform a depth first post order search
	cout << endl << "Breadth First Search: ";
	tree.BreadthFirstSearch(PrintNode);						//Perform a breadth first search
	cout << endl << endl;
	
	BinaryTree<int> tree2(tree);	//Copy constructor
	tree2.Insert(65);
	tree2.PrintDetails();

	tree2 = tree;					//= assignment operator overload
	tree2.Insert(10);
	tree2.PrintDetails();

	cout << tree << endl;			//<< operator overload

	cout << "---Finished testing Binary Tree" << endl;
}

/// <summary>
/// Test the Dynamic List.
/// </summary>
void TestDynamicList()
{
	cout << "--- Testing Dynamic List" << endl;

	List<int> list;						//Default constructor
	list.Push(30);						//Push
	list.Push(110);
	list.Push(220);
	list.Pop();							//Pop
	list.Reserve(5);					//Add more capacity
	list.PrintDetails();				//Print out details (for testing)

	List<int> list2(2);					//Overloaded constructor
	list2.Push(20);
	list2.Push(50);
	list2.Push(70);						//Increases the capacity
	list2.PrintDetails();

	list2.Insert(1, list);				//Insert list
	cout << "INSERT: ";
	list2.PrintDetails();

	List<int> list3(list);				//Copy constructor
	list3.Push(200);
	list3.PrintDetails();

	list3 = list;						//= (assignment) operator
	list3.Push(100);
	list3.PrintDetails();

	list.PrintDetails();
	cout << "List: " << list << endl;	//<< operator
	cout << "List: " << list.ToString().c_str() << endl;	//ToString

	cout << "--- Finished testing Dynamic List" << endl;
}

/// <summary>
/// Test the Dequeue.
/// </summary>
void TestDequeue()
{
	cout << "---Testing Dequeue" << endl;

	Dequeue<int> dequeue;		//Default constructor
	dequeue.PushFront(100);		//Push front
	dequeue.PushBack(200);		//Push back
	dequeue.PushFront(300);
	dequeue.PushBack(400);
	dequeue.PrintDetails();

	dequeue.PopBack();				//Pop back
	dequeue.PopFront();				//Pop front
	dequeue.PrintDetails();

	Dequeue<int> dequeue2(dequeue);		//Copy constructor
	dequeue2.PushBack(500);
	dequeue2.PrintDetails();

	dequeue2.Clear();					//Clear
	dequeue2.PrintDetails();

	dequeue2 = dequeue;			//= (assignment) operator
	dequeue2.PopBack();
	dequeue2.PrintDetails();

	cout << "List: " << dequeue << endl;	//<< operator overload

	cout << "---Finished testing Dequeue" << endl;
}

/// <summary>
/// Test the Linked List.
/// </summary>
void TestLinkedList()
{
	cout << "---Testing Linked List" << endl;

	LinkedList<int> list;			//Default contructor
	list.PushFront(10);				//Push front
	list.PushBack(20);				//Push back
	list.PushFront(30);
	list.PrintDetails();			//Print details

	list.PopBack();					//Pop back
	list.PopFront();				//Pop front
	list.PrintDetails();

	LinkedList<int> list2(list);	//Copy constructor
	list2.PushBack(100);
	list2.PrintDetails();

	list2.Clear();					//Clear list
	list2.PrintDetails();

	list2 = list;					//= (assignment) operator
	list2.PushFront(5);
	list2.PrintDetails();

	list.PushFront(100);
	list.PushBack(200);
	list.PushFront(300);
	list.PushBack(400);
	list.Remove(10);				//Remove
	list.Remove(300);				//Remove head
	list.Remove(400);				//Remove tail
	list.PrintDetails();

	list.PushFront(220);
	list.PushFront(500);
	list.PushBack(700);
	list.PushBack(1000);
	list.PrintDetails();

	cout << "List: " << list << endl;	//>> operator overload (uses the iterators)

	cout << "---Finished Testing" << endl;
}

/// <summary>
/// Test the Stack.
/// </summary>
void TestStack()
{
	cout << "---Testing Stack" << endl;

	Stack<int> stack;			//Default constructor
	stack.Push(20);				//Push to top of stack
	stack.Push(40);
	stack.Push(60);
	stack.Push(80);
	stack.Pop();
	stack.PrintDetails();		//Print details

	Stack<int> stack2(stack);	//Copy constructor
	stack2.Pop();
	stack2.PrintDetails();

	stack2.Clear();				//Clear
	stack2.PrintDetails();

	stack2 = stack;				//= (assignment) operator
	stack2.Push(100);
	stack2.PrintDetails();

	Stack<int> stack3(2);		//Overloaded constructor
	stack3.Push(100);
	stack3.Push(200);
	stack3.PrintDetails();

	cout << "List: " << stack << endl;	//<< operator

	cout << "---Finished testing Stack" << endl;
}

/// <summary>
/// Try accessing the heap by a given index to see if an exception is thrown correctly.
/// </summary>
/// <param name="heap">The heap to access.</param>
/// <param name="index">The index to access the heap at.</param>
void TryAccessHeap(Heap<int>& heap, unsigned int index)
{
	cout << "Try index " << index << ": ";
	try
	{
		cout << heap[index];
	}
	catch (const out_of_range& e)
	{
		cout << e.what();
	}
	cout << endl;
}

/// <summary>
/// Test the Binary Heap.
/// </summary>
void TestBinaryHeap()
{
	cout << "---Testing Heap" << endl;

	Heap<int> heap;				//Default constructor
	heap.Push(20);				//Push
	heap.Push(60);
	heap.Push(100);
	heap.Push(10);
	heap.Push(40);
	heap.Push(70);
	heap.PrintDetails();		//Print details

	heap.Pop();					//Pop
	heap.PrintDetails();

	heap.Remove(100);			//Remove
	heap.PrintDetails();

	cout << "Contains 40? " << heap.Contains(40) << endl;	//Contains
	cout << "Find 40: " << heap.Find(40) << endl;			//Find
	cout << "Contains 12? " << heap.Contains(12) << endl;
	cout << "Find 12: " << heap.Find(12) << endl;
	cout << endl << "Root: " << heap.Peek() << endl;		//Peek
	cout << "Root index: " << heap.GetRootIndex() << endl;	//Root Index
	cout << "Root's first child: " << heap[heap.GetFirstChild(heap.GetRootIndex())] << endl;	//Get first child
	cout << "Root's second child: " << heap[heap.GetSecondChild(heap.GetRootIndex())] << endl;	//Get second child
	cout << "Size: " << heap.Size() << endl << endl;	//Size

	TryAccessHeap(heap, 2);		//Exceptions
	TryAccessHeap(heap, 20);
	TryAccessHeap(heap, -10);
	cout << endl;

	Heap<int> heap2(heap);		//Copy constructor
	heap2.Clear();				//Clear
	heap2.PrintDetails();

	heap2 = heap;				//Assignment operator
	heap2.Push(200);
	heap2.PrintDetails();

	heap2 = Heap<int>(40);		//Overloaded constructor
	cout << "Root: " << heap2.Peek() << endl;

	cout << "Heap: " << heap << endl;	//<< operator

	cout << "---Finished testing Heap" << endl;
}

/// <summary>
/// Main entry point for the program.
/// </summary>
/// <returns></returns>
int main() 
{
	//Run tests on container classes
	if (false)
	{
		TestBinaryHeap();
		TestDynamicList();
		TestLinkedList();
		TestStack();
		TestDequeue();
		TestBinaryTree();

		//Test for memory leaks
		_CrtDumpMemoryLeaks();
	}
	//Run the centipede game
	else
	{
		// allocation
		auto app = new CentipedeGameApp();

		// initialise and loop
		app->run("Centipede", 800, 600, false);

		// deallocation
		delete app;
	}
	return 0;
}
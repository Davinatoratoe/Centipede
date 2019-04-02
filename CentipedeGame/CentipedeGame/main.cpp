#include "CentipedeGameApp.h"
#include <iostream>
#include "BinaryTree.h"
#include "DynamicList.h"

using namespace std;

template <typename T>
void PrintNode(BinaryTreeNode<T>* node)
{
	cout << node->data << " ";
}

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

int main() 
{
	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("Centipede", 720, 900, false);

	// deallocation
	delete app;

	return 0;
}
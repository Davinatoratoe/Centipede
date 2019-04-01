#include "CentipedeGameApp.h"
#include <iostream>
#include "BinaryTree.h"

using namespace std;

void TestBinaryTree()
{
	cout << "---Testing Binary Tree" << endl;

	BinaryTree<int> tree;
	//tree.PrintDetails();
	tree.Insert(20);
	//tree.PrintDetails();
	tree.Insert(10);
	//tree.PrintDetails();
	tree.Insert(30);
	//tree.PrintDetails();
	tree.Insert(15);
	//tree.PrintDetails();
	tree.Insert(25);
	//tree.PrintDetails();

	//tree.Remove(25);
	tree.PrintDetails();

	cout << "---Finished testing Binary Tree" << endl;
}

int main() {
	
	TestBinaryTree();
	return 0;

	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("Centipede", 720, 900, false);

	// deallocation
	delete app;

	return 0;
}
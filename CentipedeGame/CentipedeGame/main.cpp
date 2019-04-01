#include "CentipedeGameApp.h"
#include <iostream>
#include "BinaryTree.h"

using namespace std;

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

	tree.Remove(50);
	tree.PrintDetails();
	
	//cout << tree << endl;

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
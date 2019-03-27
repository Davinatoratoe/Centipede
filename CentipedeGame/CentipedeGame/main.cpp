#include "CentipedeGameApp.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

int main() 
{	
	cout << "Testing Linked List" << endl;
	LinkedList<int> list;
	list.PushFront(10);
	list.PushFront(20);
	list.PushBack(30);
	list.PushFront(40);
	list.PopBack();
	list.PopFront();
	list.Clear();
	list.PushFront(100);
	list.PushBack(200);
	list.PushFront(300);
	list.PushBack(400);
	list.Remove(300);
	list.Display();
	
	cout << endl << "Finished Testing" << endl;
	
	return 0;

	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
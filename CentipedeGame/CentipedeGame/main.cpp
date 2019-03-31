#include "CentipedeGameApp.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

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

int main() 
{	
	TestLinkedList();
	return 0;

	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
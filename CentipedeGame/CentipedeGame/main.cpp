#include "CentipedeGameApp.h"
#include <iostream>
#include "DynamicList.h"

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

	cout << "List: " << list << endl;	//<< operator

	cout << "--- Finished testing Dynamic List" << endl;
}

int main() 
{
	TestDynamicList();
	return 0;

	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
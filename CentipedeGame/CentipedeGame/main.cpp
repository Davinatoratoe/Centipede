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
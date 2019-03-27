#include "CentipedeGameApp.h"
#include <iostream>
#include "DynamicList.h"

int main() 
{
	cout << "Testing Dynamic List" << endl;
	
	List<int> list;
	list.Push(20);
	list.Push(100);
	list.Push(50);
	list.Pop();
	list.Clear();
	list.Push(30);
	list.Push(110);
	list.Reserve(10);

	list.Display();

	cout << endl << "Finished testing Dynamic List" << endl;


	return 0;

	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
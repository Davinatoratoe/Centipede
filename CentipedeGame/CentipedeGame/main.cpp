#include "CentipedeGameApp.h"
#include <iostream>
#include "Stack.h"

using namespace std;

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

int main() 
{
	TestStack();
	return 0;
	
	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
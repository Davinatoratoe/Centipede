#include "CentipedeGameApp.h"
#include <iostream>
#include "Dequeue.h"

using namespace std;

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

int main() 
{
	TestDequeue();
	return 0;

	// allocation
	auto app = new CentipedeGameApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
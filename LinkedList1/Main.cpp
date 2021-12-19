#include <iostream>
#include "LinkedList.h"
//https://hunter2423.tistory.com/1
using namespace std;

int main()
{
	LinkedList* list = new LinkedList();

	list->Insert(10);
	list->Insert(25);
	list->Insert(44);
	list->Display();

	cout << endl;
	list->Delete(25);
	list->Display();

	cout << endl;
	list->Delete(44);
	list->Display();

	delete list;
	return 0;
}
#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

int main()
{
	cout << "Singly Linked List Example" << endl << endl;
	//LinkedList<int> lList;
	PriorityQueue<int> lList;


	lList.Push(101,2);
	lList.Push(201,4);
	lList.Push(301,1);
	lList.Push(401,3);
	lList.Push(1,6);
	lList.Push(701,5);
	lList.Pop();

	LinkIterator<int> it;
	for (it = lList.Front(); it != lList.End(); it++)
	{
		cout << " " << *it;
	}


	cout << endl << endl;

	return 0;
}
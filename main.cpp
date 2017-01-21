#include <stdio.h>
#include <iostream>

#include "MyDoublyLinkedList.h"

using namespace std;

using namespace MyList;

int main()
{
	MyDoublyLinkedList<int> list;
	cout << "empty list\n";
	list.print();

	list.pushFront(1);
	list.pushFront(0);
	list.pushBack(2);
	cout << "pushFront 1 and 0, then pushBack 2\n";
	list.print();

	list.popFront();
	cout << "popFront\n";
	list.print();

	list.popFront();
	cout << "popFront\n";
	list.print();

	list.popFront();
	cout << "popFront\n";
	list.print();

	list.pushFront(0);
	list.pushBack(1);
	list.pushBack(2);
	cout << "pushFront 0, then pushBack 1 and 2\n";
	list.print();

	list.popBack();
	cout << "popBack\n";
	list.print();

	list.popBack();
	cout << "popBack\n";
	list.print();

	list.popBack();
	cout << "popBack\n";
	list.print();

	for (int i = 0; i < 5; i++) {
		list.insert(2, i);
		cout << "insert " << i << " in position 2 \n";
		list.print();
	}

	for (int i = 0; i < 5; i++) {
		list.erase(2);
		cout << "erase in position 2 \n";
		list.print();
	}

	cout << "The index of element 1 is " << list.indexOf(1) << "\n";
	cout << "The index of element 0 is " << list.indexOf(0) << "\n";
	cout << "The index of element 2 is " << list.indexOf(2) << "\n";

	list.pushBack(5);
	cout << "pushBack 5 \n";
	list.print();

	list.insert(2, 6);
	cout << "insert 5 in position 2 \n";
	list.print();

	cout << "The index of element 6 is " << list.indexOf(6) << "\n";

	system("PAUSE");
	return 0;
}


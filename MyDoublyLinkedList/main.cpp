#include <iostream>
#include <conio.h>

#include "doublylinkedlist.h"
#include "main.h"

using namespace std;

using namespace MyList;

void pause()
{
	cout << "Press any key to exit...";
	getch();
}

DoublyLinkedList<int> flatList;
void concatToFlatList(DoublyLinkedList<int>& list) {
	flatList.concat(list);
}

bool isEqualToSix(int& n) {
	return n == 6;
}

bool isPositive(int& n) {
	return n >= 0;
}

int main()
{
	DoublyLinkedList<int> list;
	cout << "Empty list <int>\n";
	list.print();
	
	cout << "Is it empty? " << (list.isEmpty() ? "True" : "False") << "\n";

	cout << "\n";

	list.pushFront(1);
	list.pushFront(0);
	list.pushBack(2);
	cout << "pushFront 1 and 0, then pushBack 2\n";
	list.print();
	cout << "From cout: " << list << "\n";
	cout << "is it empty? " << (list.isEmpty()? "True":"False") << "\n";

	cout << "\n";
	/*
	cout << "Copy of the list " << list << " is: \n";
	DoublyLinkedList<int> listCopy;
	cout << (listCopy = list) << "\n";
	cout << "pushBack 2 to original list\n";
	list.pushBack(2);
	cout << "Copy: " << listCopy << ". Original: " << list << "\n";

	cout << "\n";

	cout << "Initialization using initializer_list {1, 2, 3}\n";
	DoublyLinkedList<int> listIn = { 1, 2, 3 };
	cout << listIn << "\n";

	cout << "Empty initialization and then assignment using initializer_list {1, 2, 3}\n";
	DoublyLinkedList<int> listIn2;
	listIn2 = { 1, 2, 3 };
	cout << listIn2 << "\n";

	cout << "\n";

	cout << "Using list " << list << "\n";

	list.popFront();
	cout << "popFront\n";
	list.print();

	list.popFront();
	cout << "popFront\n";
	list.print();

	list.popFront();
	cout << "popFront\n";
	list.print();

	cout << "\n";

	list.pushFront(0);
	list.pushBack(1);
	list.pushBack(2);
	cout << "pushFront 0, then pushBack 1 and 2\n";
	list.print();

	cout << "\n";

	list.popBack();
	cout << "popBack\n";
	list.print();

	list.popBack();
	cout << "popBack\n";
	list.print();

	list.popBack();
	cout << "popBack\n";
	list.print();

	cout << "\n";

	for (int i = 0; i < 5; i++) {
		list.insert(2, i);
		cout << "insert " << i << " in position 2 \n";
		list.print();
	}

	cout << "\n";

	for (int i = 0; i < 5; i++) {
		list.erase(2);
		cout << "erase in position 2 \n";
		list.print();
	}

	cout << "\n";

	DoublyLinkedList<int> emptyList;
	cout << "Using list " << emptyList << "\n";
	DoublyLinkedList<int>::iterator it1 = emptyList.begin();
	emptyList.insert(it1, 5);
	cout << "insert 5 (with iterator) in position 0\n";
	cout << emptyList << "\n";
	emptyList.insert(it1, 4);
	cout << "insert 4 (with iterator) in position 0\n";
	cout << emptyList << "\n";
	emptyList.insert(++it1, 6);
	cout << "insert 6 (with iterator) in position 1\n";
	cout << emptyList << "\n";
	emptyList.erase(it1);
	cout << "erase (with iterator) in position 1 \n";
	cout << emptyList << "\n";

	cout << "\n";

	cout << "Using list " << listIn2 << "\n";
	DoublyLinkedList<int>::iterator it2 = listIn2.begin();
	it2 += 1;
	listIn2.erase(it2);
	cout << "erase (with iterator) in position 1 \n";
	listIn2.print();
	it2 -= 1;
	for (int count = 0; count < 3; count++) {
		listIn2.erase(it2);
		cout << "erase (with iterator) in position 0 \n";
		listIn2.print();
	}

	cout << "\n";

	list.pushBack(2);
	cout << "Using list " << list << "\n";
	cout << "The index of element 1 is " << list.indexOf(1) << "\n";
	cout << "The index of element 0 is " << list.indexOf(0) << "\n";
	cout << "The index of element 2 is " << list.indexOf(2) << "\n";

	cout << "\n";

	list.pushBack(5);
	cout << "pushBack 5 \n";
	list.print();

	list.insert(2, 6);
	cout << "insert 6 in position 2 \n";
	list.print();

	cout << "\n";

	cout << "The index of element 6 is " << list.indexOf(6) << "\n";

	cout << "\n";

	cout << "The head value is " << list.getHead() << "\n";
	cout << "The tail value is " << list.getTail() << "\n";
	cout << "The size of the list is " << list.getSize() << "\n";

	cout << "\n";

	DoublyLinkedList<string> listString;

	cout << "Empty list <string>\n";
	listString.print(';');

	listString.pushFront("one");
	listString.pushFront("zero");
	listString.pushBack("two");
	cout << "pushFront \"one\" and \"zero\", then pushBack \"two\"\n";
	cout << listString << "\n";

	cout << "\n";

	DoublyLinkedList<int> list2;
	cout << "Another list <int>\n";
	list2.pushFront(1);
	list2.pushFront(1);
	list2.pushFront(1);
	list2.print();

	cout << "\n";

	DoublyLinkedList<DoublyLinkedList<int>> inceptionList;
	cout << "A list of lists of <int>\n";
	cout << inceptionList << "\n";

	cout << "\n";

	inceptionList.pushBack(list);
	inceptionList.pushBack(list2);
	cout << "pushBack of the 2 <int> lists previously created\n";
	cout << inceptionList << "\n";

	cout << "\n";

	list.concat(list2);
	cout << "list concat of the 2 lists\n";
	cout << list << "\n";

	cout << "\n";

	cout << "Is every member of the list " << list << " positive? " << (list.every(isPositive) ? "True" : "False") << "\n";
	cout << "Is any member of the list " << list << " equal to 6? " << (list.any(isEqualToSix) ? "True" : "False") << "\n";
	cout << "Is every member of the list " << list << " equal to 6? " << (list.every(isEqualToSix) ? "True" : "False") << "\n";

	cout << "\n";

	inceptionList.forEach(concatToFlatList);
	cout << "Flatten of the list of lists using forEach\n";
	cout << flatList << "\n";

	cout << "\n";

	cout << "Are the 2 lists equal? " << (flatList == list ? "True" : "False") << "\n";
	flatList.pushBack(3);
	list.pushBack(1);
	cout << "pushBack of 1 to a list and 3 to the other\n";
	cout << "Are the 2 lists equal? " << (flatList == list ? "True" : "False") << "\n";

	cout << "\n";

	cout << "The element in position 2 of list " << list << " is " << list[2] << "\n";
	DoublyLinkedList<int>::iterator it3 = list.begin();
	it3 += 2;
	cout << "The element in position 2 of list " << list << " is " << list[it3] << " (done with iterator)\n";

	cout << "The element in position 6 of list " << list << " is " << list[6] << "\n";
	try {
		cout << "The element in position 8 of list " << list << " is " << list[9] << "\n";
	}
	catch (runtime_error e) {
		cout << "Attempted to get element in position 9 but got \"" << e.what() << "\" exception, as expected \n";
	}
	try {
		cout << "The element in position -1 of list " << list << " is " << list[-1] << "\n";
	}
	catch (runtime_error e) {
		cout << "Attempted to get element in position -1 but got \"" << e.what() << "\" exception, as expected \n";
	}

	cout << "\n";
	cout << "\n";
	*/

	pause();

	return 0;
}



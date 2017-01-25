#include <iostream>
#include <conio.h>

#include "DoublyLinkedList.h"

using namespace std;

using namespace MyList;

void pause()
{
	cout << "Press any key to exit...";
	getch();
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

	cout << "\n";
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
	cout << "\n";

	DoublyLinkedList<int> list2;
	cout << "Another list <int>\n";
	list2.pushFront(1);
	list2.pushFront(1);
	list2.pushFront(1);
	list2.print();

	cout << "\n";
	cout << "\n";

	DoublyLinkedList<DoublyLinkedList<int>> inceptionList;
	cout << "A list of lists of <int>\n";
	cout << inceptionList << "\n";

	cout << "\n";

	inceptionList.pushFront(list);
	inceptionList.pushFront(list2);
	cout << "pushFront of the 2 <int> lists previously created\n";
	cout << inceptionList << "\n";

	cout << "\n";
	cout << "\n";

	pause();

	return 0;
}



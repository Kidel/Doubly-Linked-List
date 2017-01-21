#pragma once

namespace MyList {

	template <class T>
	class Node
	{
	private:
		Node() = default;
		Node(const T & x) : value(x), next(0), previous(0) {}

		T value = 0;
		Node<T> * next = 0;
		Node<T> * previous = 0;

		template <class T> friend class MyDoublyLinkedList;
	};

	template <class T>
	class MyDoublyLinkedList
	{
	public:
		MyDoublyLinkedList() = default;
		MyDoublyLinkedList(const MyDoublyLinkedList<T> & l);
		~MyDoublyLinkedList();

		bool isEmpty() const;
		unsigned int getSize() const;
		T & getHead() const;
		T & getTail() const;
		MyDoublyLinkedList<T> & pushFront(const T & x);
		MyDoublyLinkedList<T> & pushBack(const T & x);
		MyDoublyLinkedList<T> & popFront();
		MyDoublyLinkedList<T> & popBack();
		MyDoublyLinkedList<T> & insert(unsigned int position, const T & x);
		MyDoublyLinkedList<T> & erase(unsigned int position);
		int indexOf(const T & x) const;

		MyDoublyLinkedList<T> & operator=(const MyDoublyLinkedList<T> & l);

		void print();

	protected:
		Node<T> * head = 0;
		Node<T> * tail = 0;
		unsigned int size = 0;
	};

	// I can’t separate the definition of my template class from its declaration
	// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

	template <class T>
	MyDoublyLinkedList<T>::MyDoublyLinkedList(const MyDoublyLinkedList<T> & list)
	{
		head = 0;
		tail = 0;
		size = 0;
		for (Node<T> * currentNode = list.head; currentNode != 0; currentNode = currentNode->next)
			push_back(currentNode->value);
	}

	template <class T>
	MyDoublyLinkedList<T>::~MyDoublyLinkedList()
	{
		Node <T> * currentNode = head;
		while (currentNode != 0)
		{
			Node <T> * successor = currentNode->next;
			delete currentNode;
			currentNode = successor;
		}
	}

	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::operator=(const MyDoublyLinkedList<T> & l)
	{
		head = l.getHead();
		tail = l.getTail();
		size = l.getSize();
	}

	template <class T>
	bool MyDoublyLinkedList<T>::isEmpty() const
	{
		return (size == 0 || head == 0 || tail == 0);
	}

	template <class T>
	unsigned int MyDoublyLinkedList<T>::getSize() const
	{
		return size;
	}

	template <class T>
	T & MyDoublyLinkedList<T>::getHead() const
	{
		return head->value;
	}

	template <class T>
	T & MyDoublyLinkedList<T>::getTail() const
	{
		return tail->value;
	}

	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::pushFront(const T & x)
	{
		Node<T> * newNode = new Node<T>(x);
		if (!isEmpty()) {
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
		else {
			head = tail = newNode;
		}
		size++;

		return *this;
	}

	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::pushBack(const T & x)
	{
		Node<T> * newNode = new Node<T>(x);
		if (!isEmpty()) {
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
		}
		else {
			head = tail = newNode;
		}
		size++;

		return *this;
	}

	/// <summary>
	/// <c>popFront</c> deletes the first element of the list (if there is one).
	/// </summary>
	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::popFront()
	{
		if (isEmpty()) return *this;

		Node<T> * oldNode = head;
		if (size > 1 && head->next != 0) {
			head = head->next;
			head->previous = 0;
		}
		else {
			head = 0;
			tail = 0;
		}
		delete oldNode;
		size--;

		return *this;
	}

	/// <summary>
	/// <c>popBack</c> deletes the last element of the list (if there is one).
	/// </summary>
	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::popBack()
	{
		if (isEmpty()) return *this;

		Node<T> * oldNode = tail;
		if (size > 1 && tail->previous != 0) {
			tail = tail->previous;
			tail->next = 0;
		}
		else {
			head = 0;
			tail = 0;
		}
		delete oldNode;
		size--;

		return *this;
	}

	/// <summary>
	/// <c>insert</c> adds an element in the desired position (starting from 0). 
	/// If the position is higher then size-1 then the element is pushed to the tail.
	/// </summary>
	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::insert(unsigned int position, const T & x)
	{
		if (position == 0 || size == 0) return pushFront(x);
		if (position >= size) return pushBack(x);

		Node<T> * currentNode = head;
		for (unsigned int i = 0; i < position; i++) {
			currentNode = currentNode->next;
		}
		Node<T> * newNode = new Node<T>(x);
		newNode->next = currentNode;
		newNode->previous = currentNode->previous;
		currentNode->previous->next = newNode;
		currentNode->previous = newNode;
		size++;

		return *this;
	}

	/// <summary>
	/// <c>erase</c> deletes an element in the desired position (starting from 0). 
	/// If the position is higher then size-1 then no element is deleted.
	/// </summary>
	template <class T>
	MyDoublyLinkedList<T> & MyDoublyLinkedList<T>::erase(unsigned int position)
	{
		if (position == 0 || size == 1) return popFront();
		if (position == size - 1) return popBack();
		if (position >= size) return *this;

		Node<T> * currentNode = head;
		for (unsigned int i = 0; i < position; i++) {
			currentNode = currentNode->next;
		}
		Node<T> * oldNode = currentNode;
		currentNode = currentNode->previous;
		currentNode->next = currentNode->next->next;
		currentNode->next->previous = currentNode;
		delete oldNode;
		size--;

		return *this;
	}

	/// <summary>
	/// <c>indexOf</c> returns the index of the first occurrence of the given element.
	/// Returns -1 if the element can't be found.
	/// </summary>
	template <class T>
	int MyDoublyLinkedList<T>::indexOf(const T & x) const
	{
		Node<T> * currentNode = head;
		for (int i = 0; i < size; i++) {
			if (currentNode->value == x) return i;
			currentNode = currentNode->next;
		}
		return -1;
	}

	template <class T>
	void MyDoublyLinkedList<T>::print()
	{
		cout << "[ ";
		Node<T> * currentNode = head;
		for (unsigned int i = 0; i < size; i++) {
			cout << currentNode->value;
			cout << " ";
			currentNode = currentNode->next;
		}
		cout << "]\n";
	}
}
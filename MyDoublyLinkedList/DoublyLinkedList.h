#pragma once
#include <sstream>
#include "Node.h"

using namespace std;

namespace MyList {

	template <class T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList() = default;
		DoublyLinkedList(const DoublyLinkedList<T> & list);
		~DoublyLinkedList();

		bool isEmpty() const;
		unsigned int getSize() const;
		T & getHead() const;
		T & getTail() const;
		DoublyLinkedList<T> & pushFront(const T & x);
		DoublyLinkedList<T> & pushBack(const T & x);
		DoublyLinkedList<T> & popFront();
		DoublyLinkedList<T> & popBack();
		DoublyLinkedList<T> & insert(unsigned int position, const T & x);
		DoublyLinkedList<T> & erase(unsigned int position);
		DoublyLinkedList<T> & concat(const DoublyLinkedList<T> & list);
		int indexOf(const T & x) const;

		DoublyLinkedList<T> & map(void(*func)(T));

		void operator=(const DoublyLinkedList<T> & list);
		bool operator==(const DoublyLinkedList<T> & list);

		string to_string(char separator = ';');
		void print(char separator = ';');

		friend ostream& operator<< (ostream& stream, DoublyLinkedList<T> list) {
			stream << list.to_string(';');
			return stream;
		}

	protected:
		Node<T> * head = 0;
		Node<T> * tail = 0;
		unsigned int size = 0;
	};

	// I can’t separate the definition of my template class from its declaration
	// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> & list)
	{
		head = 0;
		tail = 0;
		size = 0;
		concat(list);
	}

	template <class T>
	DoublyLinkedList<T>::~DoublyLinkedList()
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
	void DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> & list)
	{
		head = list.head;
		tail = list.tail;
		size = list.size;
	}

	template <class T>
	bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T> & list)
	{
		if (size == list.getSize()) {
			Node <T> * currentNode = head;
			Node <T> * currentListNode = list.head;

			while (currentNode != 0)
			{
				if (currentNode->value == currentListNode->value)
				{
					currentNode = currentNode->next;
					currentListNode = currentListNode->next;
				}
				else return false;
			}
		}
		else return false;

		return true;
	}

	template <class T>
	bool DoublyLinkedList<T>::isEmpty() const
	{
		return (size == 0 || head == 0 || tail == 0);
	}

	template <class T>
	unsigned int DoublyLinkedList<T>::getSize() const
	{
		return size;
	}

	template <class T>
	T & DoublyLinkedList<T>::getHead() const
	{
		return head->value;
	}

	template <class T>
	T & DoublyLinkedList<T>::getTail() const
	{
		return tail->value;
	}

	template <class T>
	DoublyLinkedList<T> & DoublyLinkedList<T>::pushFront(const T & x)
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
	DoublyLinkedList<T> & DoublyLinkedList<T>::pushBack(const T & x)
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
	DoublyLinkedList<T> & DoublyLinkedList<T>::popFront()
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
	DoublyLinkedList<T> & DoublyLinkedList<T>::popBack()
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
	DoublyLinkedList<T> & DoublyLinkedList<T>::insert(unsigned int position, const T & x)
	{
		if (position == 0 || size == 0) return pushFront(x);
		if (position >= size) return pushBack(x);

		Node<T> * currentNode;

		if (position < size / 2) {
			currentNode = head;
			for (unsigned int i = 0; i < position; i++)
				currentNode = currentNode->next;
		}
		else {
			currentNode = tail;
			for (unsigned int i = size - 1; i > position; i--)
				currentNode = currentNode->previous;
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
	DoublyLinkedList<T> & DoublyLinkedList<T>::erase(unsigned int position)
	{
		if (position == 0 || size == 1) return popFront();
		if (position == size - 1) return popBack();
		if (position >= size) return *this;

		Node<T> * currentNode;

		if (position < size / 2) {
			currentNode = head;
			for (unsigned int i = 0; i < position; i++)
				currentNode = currentNode->next;
		}
		else {
			currentNode = tail;
			for (unsigned int i = size - 1; i > position; i--)
				currentNode = currentNode->previous;
		}
		
		Node<T> * oldNode = currentNode;
		currentNode = currentNode->previous;
		currentNode->next = currentNode->next->next;
		currentNode->next->previous = currentNode;
		delete oldNode;
		size--;

		return *this;
	}

	template <class T>
	DoublyLinkedList<T> & DoublyLinkedList<T>::concat(const DoublyLinkedList<T> & list)
	{
		for (Node<T> * currentNode = list.head; currentNode != 0; currentNode = currentNode->next)
			pushBack(currentNode->value);
		return *this;
	}

	template <class T>
	DoublyLinkedList<T> & DoublyLinkedList<T>::map(void(*func)(T))
	{
		for (Node<T> * currentNode = head; currentNode != 0; currentNode = currentNode->next)
			(*func)(currentNode->value);
		return *this;
	}

	/// <summary>
	/// <c>indexOf</c> returns the index of the first occurrence of the given element.
	/// Returns -1 if the element can't be found.
	/// </summary>
	template <class T>
	int DoublyLinkedList<T>::indexOf(const T & x) const
	{
		Node<T> * currentNode = head;
		for (unsigned int i = 0; i < size; i++) {
			if (currentNode->value == x) return i;
			currentNode = currentNode->next;
		}
		return -1;
	}

	template <class T>
	string DoublyLinkedList<T>::to_string(char separator = ';')
	{
		ostringstream oss;

		oss << "[ ";
		Node<T> * currentNode = head;
		for (unsigned int i = 0; i < size; i++) {
			oss << currentNode->value;
			if (i < size - 1)
				oss << separator;			
			oss << ' ';
			currentNode = currentNode->next;
		}
		oss << "]";

		return oss.str();
	}

	template <class T>
	void DoublyLinkedList<T>::print(char separator = ';')
	{
		cout << to_string(separator) << "\n";
	}

	
}
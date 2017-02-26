#pragma once
#include <sstream>
#include "node.h"
#include "iterator.h"

using namespace std;

namespace MyList {

	template <class T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		DoublyLinkedList(const initializer_list<T> l);
		DoublyLinkedList(const DoublyLinkedList<T>& list);
		~DoublyLinkedList();

		typedef Iterator<T> iterator;

		iterator begin() const;
		iterator end() const;

		bool isEmpty() const;
		bool notEmpty() { return !isEmpty(); }
		int indexOf(const T& x) const;

		unsigned int getSize() const;
		T& getHead() const;
		T& getTail() const;

		DoublyLinkedList<T>& pushFront(const T& x);
		DoublyLinkedList<T>& pushBack(const T& x);
		DoublyLinkedList<T>& popFront();
		DoublyLinkedList<T>& popBack();
		DoublyLinkedList<T>& insert(unsigned int position, const T& x);
		DoublyLinkedList<T>& erase(unsigned int position);
		DoublyLinkedList<T>& insert(iterator& position, const T& x);
		DoublyLinkedList<T>& erase(iterator& position);
		DoublyLinkedList<T>& concat(const DoublyLinkedList<T>& list);

		DoublyLinkedList<T>& forEach(void(*func)(T&));
		bool every(bool(*func)(T&));
		bool any(bool(*func)(T&));

		DoublyLinkedList<T>& operator=(const initializer_list<T> l);
		DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& list);
		bool operator==(const DoublyLinkedList<T>& list);
		T& operator[](unsigned const int index);
		T& operator[](iterator& position);

		string to_string(char separator = ';');
		void print(char separator = ';');

		friend ostream& operator<< (ostream& stream, DoublyLinkedList<T> list) {
			stream << list.to_string(';');
			return stream;
		}

	protected:
		Node<T>* head = 0;
		Node<T>* tail = 0;
		unsigned int size = 0;

	private: 
		void initialize();
	};

	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList()
	{
		initialize();
	}

	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList(initializer_list<T> l) : DoublyLinkedList<T>()
	{
		*this = l;
	}

	template <class T>
	DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& list) : DoublyLinkedList<T>()
	{
		*this = list;
	}

	template <class T>
	DoublyLinkedList<T>::~DoublyLinkedList()
	{
		Node<T>* currentNode = head;
		while (currentNode != 0)
		{
			Node<T>* successor = currentNode->next;
			delete currentNode;
			currentNode = successor;
		}
	}

	template <class T>
	void DoublyLinkedList<T>::initialize()
	{
		head = new Node<T>();
		tail = new Node<T>();
		tail->previous = head;
		tail->next = 0;
		head->next = tail;
		head->previous = 0;
		size = 0;
	}

	template <class T>
	typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() const
	{
		return iterator(head->next);
	}

	template <class T>
	typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() const
	{
		return iterator(tail);
	}

	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(initializer_list<T> l)
	{
		initializer_list<T>::iterator it;
		for (it = l.begin(); it != l.end(); it++)
			pushBack(*it);

		return *this;
	}

	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& list)
	{
		concat(list);
		return *this;
	}

	template <class T>
	bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T>& list)
	{
		if (size == list.getSize()) {
			iterator it = begin();
			iterator listIt = list.begin();

			while (it != end())
			{
				if (*it == *listIt)
				{
					it++;
					listIt++;
				}
				else return false;
			}
		}
		else return false;

		return true;
	}

	template <class T>
	T& DoublyLinkedList<T>::operator[](unsigned const int index) {
		if (index < 0 || index >= size)
			throw runtime_error("Index out of bounds");
		if (index < size / 2) {
			unsigned int counter = 0;
			for (iterator it = begin(); it != end(); it++) {
				if (counter == index) return *it;
				counter++;
			}
		}
		else {
			unsigned int counter = size-1;
			for (iterator it = end() - 1; it != begin(); it--) {
				if (counter == index) return *it;
				counter--;
			}
		}
		throw runtime_error("Unexpected error");
	}

	template <class T>
	T& DoublyLinkedList<T>::operator[](iterator& position) {
		if (position.isNull())
			throw runtime_error("Index out of bounds");
		return *position;
	}

	template <class T>
	bool DoublyLinkedList<T>::isEmpty() const
	{
		return (size == 0);
	}

	template <class T>
	unsigned int DoublyLinkedList<T>::getSize() const
	{
		return size;
	}

	template <class T>
	T& DoublyLinkedList<T>::getHead() const
	{
		return head->next->value;
	}

	template <class T>
	T& DoublyLinkedList<T>::getTail() const
	{
		return tail->previous->value;
	}

	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::pushFront(const T& x)
	{
		Node<T>* newNode = new Node<T>(x);

		newNode->previous = head;
		newNode->next = head->next;
		head->next = newNode;
		newNode->next->previous = newNode;

		size++;

		return *this;
	}

	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::pushBack(const T& x)
	{
		Node<T>* newNode = new Node<T>(x);

		newNode->next = tail;
		newNode->previous = tail->previous;
		tail->previous = newNode;
		newNode->previous->next = newNode;

		size++;

		return *this;
	}

	/// <summary>
	/// <c>popFront</c> deletes the first element of the list (if there is one).
	/// </summary>
	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::popFront()
	{
		if (isEmpty()) return *this;

		Node<T>* oldNode = head->next;
		if (size > 1) {
			head->next = oldNode->next;
			head->next->previous = head;
		}
		else {
			initialize();
		}
		delete oldNode;
		size--;

		return *this;
	}

	/// <summary>
	/// <c>popBack</c> deletes the last element of the list (if there is one).
	/// </summary>
	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::popBack()
	{
		if (isEmpty()) return *this;

		Node<T>* oldNode = tail;
		if (size > 1) {
			tail->previous = oldNode->previous;
			tail->previous->next = tail;
		}
		else {
			initialize();
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
	DoublyLinkedList<T>& DoublyLinkedList<T>::insert(unsigned int position, const T& x)
	{
		if (position == 0 || size == 0) return pushFront(x);
		if (position >= size) return pushBack(x);

		iterator it;
		unsigned int counter;

		if (position < size / 2) {
			counter = 0;
			for (it = begin(); counter < position; it++)
				counter++;
		}
		else {
			counter = size - 1;
			for (it = end() - 1; counter < position; it--)
				counter--;
		}

		insert(it, x);

		return *this;
	}

	/// <summary>
	/// <c>erase</c> deletes an element in the desired position (starting from 0). 
	/// If the position is higher then size-1 then no element is deleted.
	/// </summary>
	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::erase(unsigned int position)
	{
		if (position == 0 || size == 1) return popFront();
		if (position == size - 1) return popBack();
		if (position >= size) return *this;

		iterator it;
		unsigned int counter;

		if (position < size / 2) {
			counter = 0;
			for (it = begin(); counter < position; it++)
				counter++;
		}
		else {
			counter = size - 1;
			for (it = end() - 1; counter < position; it--)
				counter--;
		}

		erase(it);

		return *this;
	}

	/// <summary>
	/// <c>insert</c> adds an element in the desired iterator position. 
	/// If the list is empty or the iterator is out of bounds then the element is pushed to the front.
	/// </summary>
	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::insert(iterator& position, const T& x)
	{
		if (size == 0 || position == begin() || position.isNull()) {
			pushFront(x);
			position = begin();
			return *this;
		}
		if (position == end() || position == end() - 1) {
			pushBack(x);
			position = end();
			return *this;
		}

		Node<T>* newNode = new Node<T>(x);
		newNode->previous = position.currentNode->previous;
		newNode->next = position.currentNode;
		position.currentNode->previous = newNode;
		newNode->previous->next = newNode;
		position = iterator(newNode);

		size++;
		return *this;
	}

	/// <summary>
	/// <c>erase</c> deletes an element in the desired iterator position. 
	/// If the list is empty or the position is null then no element is deleted.
	/// </summary>
	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::erase(iterator& position)
	{
		if (position.isNull() || size == 0 || position == end()) 
			return *this;
		if (position == begin()) {
			popFront();
			return *this;
		}
		if (position == end() - 1) {
			popBack();
			return *this;
		}

		iterator newIterator(position.currentNode->next);
		if (position.currentNode->next != 0)
			position.currentNode->next->previous = position.currentNode->previous;
		if (position.currentNode->previous != 0)
			position.currentNode->previous->next = position.currentNode->next;

		delete position.currentNode;
		position = newIterator;
		size--;

		return *this;
	}

	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::concat(const DoublyLinkedList<T>& list)
	{
		for (iterator i = list.begin(); i != list.end(); i++) 
			pushBack(i.currentNode->value);
		return *this;
	}

	/// <summary>
	/// <c>forEach</c> returns the list after the given function is applied to every member.
	/// </summary>
	template <class T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::forEach(void(*func)(T&))
	{
		for (iterator i = begin(); i != end(); i++) 
			(*func)(i.currentNode->value);
		return *this;
	}

	/// <summary>
	/// <c>every</c> returns true if every member of the list return true to the given function. 
	/// </summary>
	template <class T>
	bool DoublyLinkedList<T>::every(bool(*func)(T&))
	{
		for (iterator i = begin(); i != end(); i++) 
			if (!(*func)(i.currentNode->value)) return false;
		return true;
	}

	/// <summary>
	/// <c>any</c> returns true if at least one member of the list returns true to the given function. 
	/// </summary>
	template <class T>
	bool DoublyLinkedList<T>::any(bool(*func)(T&))
	{
		for (iterator i = begin(); i != end(); i++)
			if ((*func)(i.currentNode->value)) return true;
		return false;
	}

	/// <summary>
	/// <c>indexOf</c> returns the index of the first occurrence of the given element.
	/// Returns -1 if the element can't be found.
	/// </summary>
	template <class T>
	int DoublyLinkedList<T>::indexOf(const T& x) const
	{
		int index = 0;
		for (iterator i = begin(); i != end(); i++) {
			if (i.currentNode->value == x) return index;
			++index;
		}
		return -1;
	}

	template <class T>
	string DoublyLinkedList<T>::to_string(char separator = ';')
	{
		ostringstream oss;

		oss << "[ ";
		for (iterator i = begin(); i != end(); i++) {
			oss << i.currentNode->value;
			if (i != end() - 1)
				oss << separator;			
			oss << ' ';
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
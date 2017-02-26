#pragma once

namespace MyList
{
	template <class T>
	class Node
	{
	private:
		Node() : next(0), previous(0) {}
		Node(const T& x) : value(x), next(0), previous(0) {}
		Node(const T& x, Node<T>* n, Node<T>* p) : value(x), next(n), previous(p) {}

		T value;
		Node<T>* next;
		Node<T>* previous;

		template <class T> friend class DoublyLinkedList;
		template <class T> friend class Iterator;
	};
}
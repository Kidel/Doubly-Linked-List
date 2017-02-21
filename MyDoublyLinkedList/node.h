#pragma once

namespace MyList
{
	template <class T>
	class Node
	{
	private:
		Node() = default;
		Node(const T& x) : value(x), next(0), previous(0) {}
		Node(const T& x, Node<T>* n, Node<T>* p) : value(x), next(n), previous(p) {}

		T value = 0;
		Node<T>* next = 0;
		Node<T>* previous = 0;

		template <class T> friend class DoublyLinkedList;
		template <class T> friend class Iterator;
	};
}
#pragma once
#include "node.h"

namespace MyList
{
	template <class T>
	class Iterator
	{
	public:
		typedef Iterator<T> iterator;

		Iterator() = default;
		Iterator(Node<T>* sourceNode) : currentNode(sourceNode) { }
		Iterator(Iterator<T>* sourceIterator) : currentNode(sourceIterator.currentNode) { }

		iterator& operator=(const iterator& i);
		iterator& operator++(); //prefix
		iterator operator++(int); //postfix
		iterator& operator--();
		iterator operator--(int);
		iterator& operator+=(const int n);
		iterator& operator-=(const int n);
		iterator& operator+(const int n);
		iterator& operator-(const int n);
		bool operator==(const iterator& i) const;
		bool operator!=(const iterator& i) const;

		bool isNull() { return currentNode == 0; }
		bool notNull() { return !isNull(); }

	protected:
		Node<T>* currentNode = 0;
		T& operator*();  // dereferencing operator

		template <class T> friend class DoublyLinkedList;
	};

	template <class T>
	T& Iterator<T>::operator*()
	{
		return currentNode->value;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator=(const iterator& i)
	{
		currentNode = i.currentNode;
		return *this;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator+=(const int n)
	{
		(*this) = (*this) + n;
		return *this;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator-=(const int n)
	{
		(*this) = (*this) - n;
		return *this;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator+(const int n)
	{
		iterator app = (*this);
		for (int i = 0; i < n; i++)
			++app;
		return app;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator-(const int n)
	{
		iterator app = (*this);
		for (int i = 0; i < n; i++)
			--app;
		return app;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator++()
	{
		currentNode = currentNode->next;
		return *this;
	}

	template <class T>
	Iterator<T> Iterator<T>::operator++(int)
	{
		iterator result(*this);
		++(*this);
		return result;
	}

	template <class T>
	Iterator<T>& Iterator<T>::operator--()
	{
		currentNode = currentNode->previous;
		return *this;
	}

	template <class T>
	Iterator<T> Iterator<T>::operator--(int)
	{
		iterator result(*this);
		--(*this);
		return result;
	}

	template<class T>
	bool Iterator<T>::operator==(const iterator& i) const
	{
		return (this->currentNode == i.currentNode);
	}

	template <class T>
	bool Iterator<T>::operator!=(const iterator& i) const
	{
		return !(this->currentNode == i.currentNode);
	}
}
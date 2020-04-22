#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <iostream>
#include <exception>
#include <stdexcept>

template<typename T>

class AbstractList
{
	protected:
		unsigned int numElements;
		Node<T> * head;
	public:
		AbstractList();
		virtual ~AbstractList();
		virtual void append(T x) = 0;
		virtual T remove() = 0;
		bool isEmpty() const;
};

template<typename T>

AbstractList<T>::AbstractList()
{
	numElements = 0;
	head = NULL;
}

template<typename T>

AbstractList<T>::~AbstractList()
{
	while(head != NULL)
	{
		Node<T> *temp = head;
		head = head->getNext();
		delete(temp);
	}
}

template<typename T>

bool AbstractList<T>::isEmpty() const
{
	return(head == NULL);
}


// ===================================================================
template<typename T>

class List: public AbstractList<T>
{
	public:
		List()
		{
			head = NULL;
		}
		
		void append(T x)
		{
			head = new Node<T>(x,head);
		}

		T remove()
		{
			if (head == NULL)
				throw std:: underflow_error("Can't remove from empty list");
			T val = head ->getValue();
			head = head -> getNext();
			return val;
		}

		void append_tail(T x)
		{
			Node<T>* tmp = head;
			if (tmp == NULL)
				tmp = new Node<T>(x,NULL);
			else
			{
				while (tmp -> getNext() != NULL)
				{
					tmp = tmp -> getNext();
				}
				tmp -> setNext(new Node<T>(x,NULL));
			}
		}

		void insert(T x, int pos)
		{
			Node<T>* tmp = head;
			Node<T>* prev;
			while(tmp != NULL && pos > 0)
			{
				prev = tmp;
				tmp = tmp -> getNext();
				pos--; 
			}
			if(pos != 0)
				throw std::underflow_error("Index out of bound");
			if (tmp == head)
				head = new Node<T>(x, head);
			else
				prev -> setNext(new Node<T>(x, prev -> getNext()));
		}

		T remove_at(int pos)
		{
			Node<T>* tmp = head;
			Node<T>* prev;
			while(tmp != NULL && pos >0)
			{
				prev = tmp;
				tmp = tmp->getNext();
				pos--;
			}
			if(pos != 0)
				throw std::underflow_error("Index out of bound.");
			T elem = tmp -> getValue();
			if(tmp == head)
				head = head -> getNext();
			else
				prev -> setNext(tmp -> getNext());
			return elem;
		}

		void print()
		{
			Node<T> *tmp = head;
			while(tmp != NULL)
			{
				std::cout << tmp -> getValue() << std::endl;
				tmp = tmp -> getNext();
			}
		}

		T operator[](T x)
		{
			Node<T> *tmp = head;
			Node<T> *prev;
			while(tmp != NULL && x > 0)
			{
				prev = tmp;
				tmp = tmp -> getNext();
				x--;
			}
			if(x != 0)
			{
				throw std::underflow_error("Index out of bound.");
			}
			T ind  = tmp -> getValue();

			return ind;
		}		

		friend std::ostream& operator<< (std::ostream &out,  List<T> &L)
		{
			Node<T> *tmp = L.head;
			while(tmp != NULL)
			{
				std::cout << tmp -> getValue() << std::endl;
				tmp = tmp -> getNext();
			}
			return out;
		}

	private:
		Node<T>* head;
};






#endif
//end of List.h
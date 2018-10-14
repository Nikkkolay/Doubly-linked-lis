#pragma once
#include "BiList.h"
#include "Node.h"
template<typename T>
class Iterator
{
	template<typename T1>friend void Print(Iterator<T1> F, const Iterator<T1 > &S);
	template<typename T1>friend void Sort(const Iterator<T1> &F, const Iterator<T1> &S);
	template<typename T1>friend void Rem(BiList<T1>& List, Iterator<T1>& F);
	template<typename T1>friend void RemBetween(BiList<T1>& List, const Iterator<T1>& F,const Iterator<T1>& S);
	template<typename T1>friend void RemDuplicates(BiList<T1>& List, const Iterator<T1>& F, const Iterator<T1>& S);
public:
	Iterator();
	Iterator(const Node<T> &N);
	Iterator(Node<T> *N);
	Iterator(const Iterator<T>& N);

	void operator=(const Node<T>& N);
	void operator=(Node<T>* N);
	void operator=(const Iterator<T> & N);

	void show();
	Iterator<T> operator + (int step) const;
	Iterator<T> operator ++ (int);
	Iterator<T> operator - (int step) const;



	bool operator==(const Iterator& A);
	bool operator!=(const Iterator& A);

//private:
	Node<T> * ptrNode;
	T& getData()
	{
		return (ptrNode->data);
	}
};

template<typename T>
void Print(Iterator<T> F, const Iterator<T> &S)
{
	if (F.ptrNode != nullptr)
		for (;; F++)
		{
			cout << (F.getData()) << endl;
			if ((F == S) || (F.ptrNode->pNext) == nullptr)
				break;
		}
}

template<typename T1>
inline void Sort(const Iterator<T1>& F, const Iterator<T1>& S)
{
	if (F.ptrNode != nullptr)
		for (Iterator<T1> I = F;; I++)
		{
			for (Iterator<T1> J = F;; J++)
			{
				if (I.ptrNode->data < J.ptrNode->data)
				{
					T1 temp = I.ptrNode->data;
					I.ptrNode->data = J.ptrNode->data;
					J.ptrNode->data = temp;
				}
				if (J == S || J.ptrNode->pNext == nullptr)
					break;
			}
			if (I == S || I.ptrNode->pNext == nullptr)
				break;
		}
}


template<typename T1>
inline void Rem(BiList<T1>& List, Iterator<T1> & F)
{
	if (List.size != 0)
	{
		if (List.size == 1)
		{
			delete F.ptrNode;
			F.ptrNode = nullptr;
		}
		else
		{
			if (F.ptrNode == List.head)
			{
				F.ptrNode = (List.head)->pPrev;
				List.PopFront();
			}
			else if (F.ptrNode == List.tail)
			{
				F.ptrNode = (List.tail)->pNext;
				List.PopBack();
			}
			else
			{
				Node<T1> *temp = F.ptrNode;
				if (temp->pPrev != nullptr)
					F.ptrNode = temp->pPrev;
				else
					F.ptrNode = temp->pNext;

				(temp->pNext)->pPrev = temp->pPrev;
				(temp->pPrev)->pNext = temp->pNext;
				delete temp;
				List.size--;
			}

		}
	}
	
}
template<typename T1>
inline void RemBetween(BiList<T1>& List,const Iterator<T1>& F,const Iterator<T1>& S)
{
	Iterator<T1> I1 = S - 1;
	while (I1 != F)
		Rem(List, I1);
}

template<typename T1>
inline void RemDuplicates(BiList<T1>& List, const Iterator<T1>& F, const Iterator<T1>& S)
{
	Iterator<T1> I = F, B;
	while (I != S && I != List.End())
	{
		//B = I + 1;
		
		if (I.getData() == (I+1).getData())
		{ 
			B = I + 1;
			Rem(List, B);
		}
			
		else try { I++; }
		catch (int i) { cout << "Error#" << i << endl; }
	}
}
;

template<typename T>
inline Iterator<T>::Iterator()
{
	ptrNode = nullptr;
}

template<typename T>
inline Iterator<T>::Iterator(const Node<T>& N)
{
	ptrNode = &N;
}

template<typename T>
inline Iterator<T>::Iterator(Node<T>* N)
{
	ptrNode = N;
}

template<typename T>
inline Iterator<T>::Iterator(const Iterator<T>&  N)
{
	ptrNode = N.ptrNode;
}

template<typename T>
inline void Iterator<T>::operator=(const Node<T> &N)
{
	ptrNode = &N;
}

template<typename T>
inline void Iterator<T>::operator=(Node<T> *N)
{
	ptrNode = N;
}

template<typename T>
inline void Iterator<T>::operator=(const Iterator<T> & N)
{
	ptrNode = N.ptrNode;
}

template<typename T>
void Iterator<T>::show()
{
	cout << (ptrNode->data);
}

template<typename T>
inline  Iterator<T> Iterator<T>::operator+(int step) const
{
	Node<T> *temp = ptrNode;
	if (step >= 0)
	{
		for (int i = 0; i < step; i++)
		{
			if (!temp->pNext)
				throw 2;
			temp = temp->pNext;
		}
		Iterator<T> A(temp);
		return A;
	}
	else
	{
		step *= -1;
		for (int i = 0; i < step; i++)
		{
			if (!temp->pPrev)
				throw 2;
			temp = temp->pPrev;
		}
		Iterator<T> A(temp);
		return A;
	}
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++(int)
{
	if (ptrNode->pNext == nullptr)
		throw 2;
	else ptrNode = ptrNode->pNext;
	Iterator<T> A(ptrNode);
	return A;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator-(int step) const
{
	Node<T> *temp = ptrNode;
	if (step >= 0)
	{
		for (int i = 0; i < step; i++)
		{
			if (!temp->pPrev)
				throw 2;
			temp = temp->pPrev;
		}
		Iterator<T> A(temp);
		return A;
	}
	else
	{
		step *= -1;
		for (int i = 0; i < step; i++)
		{
			if (!temp->pNext)
				throw 2;
			temp = temp->pNext;
		}
		Iterator<T> A(temp);
		return A;
	}
}

template<typename T>
inline bool Iterator<T>::operator==(const Iterator & A)
{
	if (ptrNode == A.ptrNode)
		return true;
	else
		return false;
}

template<typename T>
inline bool Iterator<T>::operator!=(const Iterator & A)
{
	if (ptrNode == A.ptrNode)
		return false;
	else
		return true;
}

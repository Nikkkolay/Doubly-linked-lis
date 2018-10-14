#pragma once
//#include "Node.h"

template<typename T>
class Node
{
	template<typename>friend class Iterator;
	template<typename>friend class BiList;
	template<typename T1>friend void Print(Iterator<T1> F, const Iterator<T1 > &S);
	template<typename T1>friend void Sort(const Iterator<T1> &F, const Iterator<T1> &S);
	template<typename T1>friend void Rem(BiList<T1>& List, Iterator<T1>& F);
	template<typename T1>friend void RemBetween(BiList<T1>& List, const Iterator<T1>& F,const Iterator<T1>& S);
	template<typename T1>friend void RemDuplicates(BiList<T1>& List, const Iterator<T1>& F, const Iterator<T1>& S);
	Node * pNext, *pPrev;
	T data;

	Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr)
	{
		this->data = data;
		this->pPrev = pPrev;
		this->pNext = pNext;
	}
	~Node()
	{
		pPrev = nullptr;
		pNext = nullptr;
	}
};
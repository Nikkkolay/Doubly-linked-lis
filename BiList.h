#pragma once
#include "Node.h"
#include "Iterator.h"

template<typename T>
class BiList
{
	template<typename> friend class Iterator;
	template<typename T1>friend void Rem(BiList<T1>& List, Iterator<T1>& F);
	template<typename T1>friend void RemBetween(BiList<T1>& List, const Iterator<T1>& F,const Iterator<T1>& S);
	template<typename T1>friend void RemDuplicates(BiList<T1>& List, const Iterator<T1>& F, const Iterator<T1>& S);
private:
	int size;
	Node<T> *head, *tail;
public:
	BiList();
	BiList(BiList& A);
	void operator=(BiList& A);
	~BiList();

	//���������� �����
	void PushFront(T data);
	void PushBack(T data);
	bool PushAfter(T after, T data);

	//�������� �����
	void PopFront();
	void PopBack();
	bool Remove(T data);
	void Clear();

	//������ � ������
	T& operator[](int index);
	int GetSize();
	Iterator<T> Begin();
	Iterator<T> End();
};

template<typename T>
BiList<T>::BiList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<typename T>
BiList<T>::BiList(BiList & A)
{
	head = nullptr;
	tail = nullptr;
	size = 0;
	for (Node<T> *i = head; i; i = i->pNext)
		PushBack(i->data);
}

template<typename T>
void BiList<T>::operator=(BiList & A)
{
	clear();
	for (Node<T> *i = head; i; i = i->pNext)
		PushBack(i->data);
}

template<typename T>
BiList<T>::~BiList()
{
	Clear();
}

//���������� �������� � ������ ������
template<typename T>
void BiList<T>::PushFront(T data)
{
	size++;
	if (size == 1)
	{
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		Node<T> *tmp = new Node<T>(data, nullptr, head);
		head->pPrev = tmp;
		head = tmp;
	}
}

//���������� �������� � ����� ������
template<typename T>
void BiList<T>::PushBack(T data)
{
	size++;
	if (size == 1)
	{
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		Node<T> *temp = new Node<T>(data, tail, nullptr);
		tail->pNext = temp;
		tail = temp;
	}
}

//��������� ������� data ����� ������� ��������� ���������� � after � ���������� true, ���� ���������� �� ������� ���������� false
template<typename T>//erre
bool BiList<T>::PushAfter(T after, T data)
{
	for (Node<T> *index = head; index; index = index->pNext)
	{
		if (index->data == after)
		{
			Node<T> *temp = new Node<T>(data, index, index->pNext);
			if (index == tail)
			{
				tail->pNext = temp;
				tail = temp;
			}
			else
			{
				(index->pNext)->pPrev = temp;
				index->pNext = temp;
			}
			size++;
			return true;
		}
	}
	return false;
}

//������� ������� �� ������ ������
template<typename T>
void BiList<T>::PopFront()
{
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size--;
	}
	else if (size>1)
	{
		Node<T> *tmp = head;
		head = head->pNext;
		delete tmp;
		head->pPrev = nullptr;
		size--;
	}
}

//������� ������� � ����� ������
template<typename T>
void BiList<T>::PopBack()
{
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size--;
	}
	else
	{
		Node<T> *tmp = tail;
		tail = tail->pPrev;
		delete tmp;
		tail->pNext = nullptr;
		size--;
	}
}

//������� ������ ������� ����������� � data � ���������� true, ���� ������ �������� ��� ���������� false
template<typename T>
bool BiList<T>::Remove(T data)
{
	for (Node<T> *index = head; index; index = index->pNext)
		if (index->data == data)
		{
			if (index == head)
				PopFront();
			else if (index = tail)
				PopBack();
			else
			{
				(index->pNext)->pPrev = index->pPrev;
				(index->pPrev)->pNext = index->pNext;
				delete index;
			}
			size--;
			return true;
		}

	return false;
}

//������� ��� �������� ������
template<typename T>
void BiList<T>::Clear()
{
	while (size)
		PopFront();
}

//������ � ������ �������� ������ �� �������. ���������������, ��������� �(N).
template<typename T>
T & BiList<T>::operator[](int index)
{
	if (index < 0 || index >= size)
		throw 1;
	if (index < size / 2)//���� ������� ����� � ������ ������
	{
		Node<T> *temp = head;
		for (int i = 0; i < index; i++)
			temp = temp->pNext;
		return temp->data;
	}
	else//���� ������� ����� � ������
	{
		Node<T> *temp = tail;
		for (int i = 0; i < size - 1 - index; i++)
			temp = temp->pPrev;
		return temp->data;
	}
}

template<typename T>
int BiList<T>::GetSize()
{
	return size;
}

//���������� ������ ������� ������ ��� ��������� 
template<typename T>
Iterator<T> BiList<T>::Begin()
{
	Iterator<T> I(head);
	return I;
}

//���������� ��������� ������� ������ ��� ��������� 
template<typename T>
Iterator<T> BiList<T>::End()
{
	Iterator<T> I(tail);
	return I;
}
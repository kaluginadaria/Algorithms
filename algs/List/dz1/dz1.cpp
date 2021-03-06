// dz1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
struct Node      
{
	int Index;    
	Node *Next; 
};

class List   //Создаем тип данных Список
{
	int size;
	Node *Head, *Tail; 
public:
	List() :Head(NULL), Tail(NULL) {};
	~List(); 
	
	void Add(int x); 
	int Kill(int k);
};

List::~List() 
{
	while (Head) 
	{
		Head = NULL;
		delete Head; 
		
	}
}

void List::Add(int x)
{
	Node *temp = new Node; 
	temp->Next = Head;  
	temp->Index = x;

	if (Head != NULL) 
	{
		
		Tail->Next = temp; 
		Tail = temp; 
	}
	else 
	{
		
		Head = Tail = temp; 
	}
	size++;
}



int List::Kill(int k) {
	Node *pointer = Head;
	while (size > 1)
	{


		for (int i = 0; i < k - 2; i++)
		{
			pointer = pointer->Next; //предыдущий от удаляемого
		}
		Node* del = pointer->Next;
		pointer->Next = pointer->Next->Next; 
		delete del;
		pointer = pointer->Next;
		size--;
	}
	pointer->Next = NULL;
	return pointer->Index;

}
//int getres(int n, int k) {
//	return n > 1 ? (getres(n - 1, k) + k - 1) % n + 1 : 1;
//}

int main()
{

	int n, k;
	cin >> n >> k;
	List lst; 
	for (int i = 1; i <= n; i++)
	{
		lst.Add(i);
	}

	cout<< lst.Kill(k);
	//cout<<getres(n, k);
	
    return 0;
}


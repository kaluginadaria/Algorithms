// dz3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <iostream>

using namespace std;




class Deque {
public:

	explicit Deque(int size);
	~Deque();


	void PushFront(int data);
	void PushBack(int data);
	int PopFront();
	int PopBack();

	bool IsEmpty() const { return head == tail; }
	void CopyArray(int* newBuffer, int newSize);
	void CreateNewBuffer(int new_size);

private:
	int *buffer;
	int buffer_size;
	int head;
	int tail;
};

Deque::Deque(int size) :
	buffer_size(size),
	tail(0),
	head(0)
{
	buffer = new int[size];
}

Deque::~Deque()
{
	delete[] buffer;
}

void Deque::PushBack(int data)
{

	if ((tail + 1 % buffer_size) == head) { 
		CreateNewBuffer(buffer_size);
		

	}
	buffer[tail] = data;
	
	tail = (tail + 1) % buffer_size; //сдвигаем хвост


}

void Deque::PushFront(int data)
{
	int check = (head == 0) ? (buffer_size - 1) : (head - 1); // предполагаемая след голова

	if (check == tail) { //если совпадет то выделяем
		
		CreateNewBuffer(buffer_size);
		head = (head == 0) ? (buffer_size - 1) : (head - 1); //сдвигаем
	}
	else {
		head = check; //сдвигаем
	}
	buffer[head] = data;



}

int Deque::PopFront()
{
	
	int data = buffer[head];
	

	head = (head + 1) % buffer_size;
	return data;
}

int Deque::PopBack()
{
	int prev = (tail == 0) ? (buffer_size - 1) : (tail - 1);
	
	int data = buffer[prev];
	tail = prev;

	return data;
}

void Deque::CreateNewBuffer(int size) {
	int new_size = size * 2; //удваиваем массив
	int *new_buffer = new int[new_size];
	CopyArray(new_buffer, new_size);
	delete[]buffer;
	buffer = new_buffer;
	buffer_size = new_size;
	//delete[]new_buffer;
}
void Deque::CopyArray(int* new_buffer, int new_size) {


	if (tail <= head)   // (_ _ t _ _ _ h _ _ _) 
	{

		copy(buffer + head, buffer + buffer_size, new_buffer); // (h _ _ _ _ _ _)
		copy(buffer, buffer + tail, new_buffer + buffer_size - head);//(h_ _ _ _ _ _t)
		head = 0;
		tail = buffer_size - 1;

	}
	else //(_ _ _ _ h _ _ _ t _ _)
	{
		copy(buffer + head, buffer + tail, new_buffer);//(h _ _ _ t)
		head = 0;

	}




}

int main()
{
	int commandsCount = 0;
	std::cin >> commandsCount;
	assert(commandsCount >= 0);

	Deque deque(10);
	for (int i = 0; i < commandsCount; ++i) {
		int command = 0;
		int value = 0;
		std::cin >> command >> value;
		switch (command) {
		case 1:
			deque.PushFront(value);
			break;
		case 4:
			if (deque.IsEmpty() && value != -1 || !deque.IsEmpty() && deque.PopBack() != value) {
				std::cout << "NO";
				return 0;
			}
			break;
		case 3:
			deque.PushBack(value);
			break;
		case 2:
			if (deque.IsEmpty() && value != -1 || !deque.IsEmpty() && deque.PopFront() != value) {
				std::cout << "NO";
				return 0;
			}
			break;
		default:
			assert(false);
		}
	}
	std::cout << "YES";
	return 0;
}
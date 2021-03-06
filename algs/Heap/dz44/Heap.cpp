// dz44.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
struct Elem {
	int Data;
	int Index;
	Elem() = default;
	Elem(int data, int index) : Data(data), Index(index) {};
	int getData() {
		return this->Data;
	}
	int getIndex() {
		return this->Index;
	}
};
bool operator < (const Elem& l, const Elem& r) {
	
		return l.Data < r.Data;
}
template<class T>
class Heap {
private:
	vector<T> heap;
	int heap_size;
public:
	Heap(int size);// создать конструктор от масива
	Heap(T* array,  int size);
	~Heap() { heap.clear(); }
	
	void Add(T value);
	void Heapify(int index);
	T GetMax();
	void ExtractMax();
	bool IsEmpty() { return heap_size == 0; }
	
};


template<class T>
void Heap<T>::Add(T value) {
	int cur = heap_size;
	heap.push_back(value);
	heap_size++;
	if (heap_size > 1) {
		for (int i = (cur - 1) / 2; ; ) {

			Heapify(i);
			if (i == 0) break;
			i = (i-1) / 2;
		}

	}
}
template<class T>
void Heap<T>::Heapify(int index) {
	int parent, left_child, right_child;
	T t;
	for (;;) {
		parent = index;
		left_child = 2 * index + 1;
		right_child = 2 * index + 2;
		if (left_child < heap_size && heap[parent] < heap[left_child]  ) {
			parent = left_child;
			
		}
		if (right_child < heap_size && heap[parent] < heap[right_child]  ) {
			parent = right_child;
			
		}
		if (parent == index) break;
		t = heap[index];
		heap[index] = heap[parent];
		heap[parent] = t;
		index = parent;
	}
	

}
template<class T>
T Heap<T>::GetMax() {
	
	Elem k = heap[0];
	 return k;
}
template<class T>
void Heap<T>::ExtractMax() {
	heap[0] = heap[heap_size - 1];
	heap.pop_back();
	heap_size--;
	Heapify(0);
}

template<class T>
Heap<T>::Heap(int size) {
	
	heap = new T[size];
	heap_size = 0;
}
template<class T>
Heap<T>::Heap(T* array, int size) {

	
	heap_size = 0;
	for (int i = 0; i < size; i++)
	{
		heap.push_back(array[i]);
		heap_size++;

	}
	for (int i = (size-1)/2; i >= 0; i--)
	{
		Heapify(i);
	};
	
	
}

 int GetResult(Heap<Elem> &heap, int l, int r) {
	if (l == 0) return heap.GetMax().getData();
	int ind = heap.GetMax().Index;
	while ( ind < l || ind > r) {
		heap.ExtractMax();
		ind = heap.GetMax().getIndex();
	}
	
	return heap.GetMax().getData();
	
}
int main()
{
	int array_size;
	int wind_size;
	cin >> array_size;
	
	Elem *array = new Elem[array_size];
	
	int value;
	for (int i = 0; i < array_size; i++)
	{
		
		cin >> value;
		array[i] =  Elem(value,i);
		
		
	}
	
	cin >> wind_size;
	if (array_size == 0 || wind_size == 0 || wind_size > array_size ) return 0;
	Heap<Elem> h(array, wind_size);
	
	int left = 0;
	int right = wind_size - 1;
	cout << GetResult(h, left, right)<< " ";
	
	for (int i = wind_size; i < array_size ; i++) {
		h.Add(array[i]);
		left++;
		right++;
		cout << GetResult(h, left, right) << " " ;
	}
	

	delete[] array;
    return 0;
}


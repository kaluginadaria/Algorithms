// dz6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int median(int* array, int l, int m, int r) {
	int a[] = { array[l], array[m], array[r] };
	if (a[1] < a[0]) {
		swap(a[0], a[1]);
		swap(l, m);
	}

	if (a[1] > a[2]) {
		swap(a[1], a[2]);
		swap(m, r);
	}

	if (a[0] > a[1])
	{
		swap(l, m);
		swap(a[0], a[1]);
	}

	return m;

}
int partition(int *array, int left, int right) {
	right--;
	if (left == right) return left; //если один элемент то возвращаем его индекс
	//находим медиану трех
	int mid = left+(right - left) / 2;
	int pivot_pos = 0;
	pivot_pos = median(array, left, mid, right);

	//меняем местами порный и первый
	swap(array[left], array[pivot_pos]);
	pivot_pos = left;
	int i = left;
	int j = right;
	while (j != left) {
		if (array[j] > array[pivot_pos] && j < i) { //если тек больше опорного и миньшие элементы уже встречались
			swap(array[j], array[i]);
			j--;
			i--;
			continue;
		}
		if (array[j] > array[pivot_pos]) { //если не встречались меньше опорного
			j--;
			continue;
		}
			

		if (array[j] <= array[pivot_pos]&& i ==left) { // начало диапозона элементов которые меньше опорного
			i = j;
			j--;
			continue;
		}
		
		j--;//если диапозон меньших уже есть продожаем
			
	}
	
	swap(array[j], array[i]);
	
	return i;

	

}
int findOrderStatistic(int* array, int size, int k) {
	int left = 0, right = size;
	while (true) {
		int m = partition(array, left, right); //передаем первый и следующий за последним
		
		if (m == k) {
			return array[m];
		}
		else if (k < m) {
			right = m;
		}
		else {
			
			left = m + 1;
		}
	}
}


int main()
{

	int n; 
	int k;
	
		cin >> n;
		cin >> k;
		int * array = new int[n];
		for (int i = 0; i < n; i++)
		{
			cin >> array[i];
		}
		cout << findOrderStatistic(array, n, k)<< endl;
	
		delete[] array;

    return 0;
}


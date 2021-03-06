// dz2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int BinSearch(int *array, int value, int l, int r) {
	int m;

	while (true) {
		m  = (l + r) / 2;
		//бинарный обычный
		if (value < array[m]) {
			r = m;
		}
		else if (value > array[m]) {
			l = m;
		}
		else {
			return m;
		}
		if (r - l == 1) //если осталось два элемента возвращаем ближайший
		{
			if (abs(value - array[l]) <= abs(value - array[r]))
				return l;
			else
				return r;
		}

	}
	
	

}
int FindResult(int* array, int value, int l, int r) {
	if (value <= array[l]) // если число меньше первого элемента возвращаем его
		return l;
	int index = 0; //индексы 0,1,2,4,8,16.....
	int j = 0; // степень двойки
	while (true) {
		if (value < array[index])
		{
			l = (j == 1) ? 0 : (int)pow(2, j - 1); //левая граница 2^(j-1)
			r = index; //2^(j)
			break;
		}
		index = (int)pow(2, j); //получаем след индекс
		j++; 
		if (index > r) //если вышли за пределы массива в левую границу передаем предыдущий индекс и выходим
			l = (int)pow(2, j - 1);
			break;
	}
	int m = 0;

	int res = BinSearch(array, value, l, r);
	return res;

}


int main()
{
	int size_a, size_b;
	cin >> size_a;
	int* a_arr = new int[size_a];
	for (int i = 0; i < size_a; i++)
	{
		cin >> a_arr[i];
	}
	cin >> size_b;
	int* b_arr = new int[size_b];
	for (int i = 0; i < size_b; i++)
	{
		cin >> b_arr[i];
	}
	for (int i = 0; i < size_b; i++)
	{
		cout << FindResult(a_arr, b_arr[i], 0, size_a) << " ";//
	}
	delete[] a_arr;
	delete[] b_arr;
    return 0;
}


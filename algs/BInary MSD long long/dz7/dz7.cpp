// dz7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>>
using namespace std;
int GetDigitByBit(int value, int bit) {
	value = value >> bit;
	return value & 1;
}
int Partition(long long *array, int left, int right, int pivot, int bit) {
	
	if (left == right) return left; 
	
	
	
	int i = -1;
	int j = left;
	while (j <= right) {
		int dig = GetDigitByBit(array[j], bit);
		if (dig <= pivot && i>=0) { 
			swap(array[j], array[i]);
			j++;
			i++;
			continue;
		}
		if (dig <= pivot) {
			j++;
			continue;
		}


		if (dig > pivot && i == -1) { 
			i = j;
			j++;
			continue;
		}

		j++;

	}

	
	if (i == -1) return ++right;
	return i;



}


int Sort(long long *array, int left, int right, int bit) {
	if (left == right) return left;
	int i = left;
	int j = right;
	do{
		while (GetDigitByBit(array[i], bit) == 0  && i <j) i++;
		while (GetDigitByBit(array[j], bit) == 1 && j > i) j--;
		swap(array[i], array[j]);
		if (j - i == 1) break;
	} while (i < j);
	if (i == j && j == right)
	{
		if (GetDigitByBit(array[i], bit) == 1) return j;

		return ++right;
	}
	
	return j;
}
void BinaryMSD(long long *arr, int l, int r, int bit) {
	if (l >= r || bit < 0) return;

	int m = Sort(arr, l, r, bit);
	bit--;
	BinaryMSD(arr, l, m - 1, bit);
	BinaryMSD(arr, m, r, bit);

}
void BinaryMSDWithPartition(long long *arr, int l, int r, int bit) {
	if (l == r || bit < 0) return;

	int m = Partition(arr, l, r, 0, bit);
	bit--;
	BinaryMSD(arr, l, m - 1, bit);
	BinaryMSD(arr, m, r, bit);

}

int main()
{
	int size;
	cin >> size;
	long long *arr = new long long[size];
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	int bit_index = 63;
	int left = 0;
	int right = size -1;
	BinaryMSD(arr, left, right, bit_index);

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	delete[] arr;
    return 0;
}


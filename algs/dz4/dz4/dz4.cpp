// dz4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <utility>
using namespace std;

struct Point {
	int X = 0;
	int Delta = 0;

	Point() = default;
	Point(int x, int delta) : X(x), Delta(delta) {}
	
};


bool isLess (const Point& l, const Point& r) {
	if (l.X == r.X)
		return l.Delta < r.Delta;
	return l.X < r.X;
}
//
//
//// мердж  из лекции
//
//template <class T>
//void MergeSort(T* arr, int aLen)
//{
//	if (aLen <= 1) {
//		return;
//	}
//	int firstLen = aLen / 2;
//	int secondLen = aLen - firstLen;
//	MergeSort(arr, firstLen);
//	MergeSort(arr + firstLen, secondLen);
//	T* c = new T[aLen];
//	Merge(arr, firstLen, arr + firstLen, secondLen, c, isLess);
//	memcpy(arr, c, sizeof(int) * aLen);
//	delete[] c;
//}
//
//template <class T, class Compare>
//void Merge(T* arr, int a_len, T* b, int b_len, T* c, Compare cmp) {
//	int i = 0;
//	int j = 0;
//	for (; i < a_len && j < b_len; ) {
//		if (cmp(arr[i], b[j])) {
//			c[i + j] = arr[i];
//			++i;
//		}
//		else {
//			c[i + j] = b[j];
//			++j;
//		}
//	}
//	for (; j < b_len; ++j) {
//		c[i + j] = b[j];
//	}
//	
//		for (; i < a_len; i++)
//		{
//			c[i + j] = arr[i];
//		}
//	
//}
//int findresult(int* array, int size){
//	Point* points = new Point[size];
//	for (int i = 0; i < size - 1; ) {
//		points[i].X = array[i];
//		points[i + 1].X = array[i + 1];
//		points[i].Delta = 1;
//		points[i + 1].Delta = -1;
//		i+=2;
//	}
//
//	
//	MergeSort(points, size);
//	/*for (int i = 0; i < size; ++i) {
//		cout << points[i].X << ' ' << points[i].Delta << endl;
//	}*/
//	int layers = 0;
//	int segs = 0;
//	int l = 0;
//	int r = 0;
//	for (int i = 0; i < size; ++i) {
//		
//		if (points[i].Delta == 1) {
//			if (layers == 0)
//				l = points[i].X;
//			layers++;
//		}
//		else layers--;
//		if (layers == 0)
//			segs+=points[i].X-l;
//	}
//	delete[] points;
//	return segs;
//}
//
//
//int main()
//{
//	int seg_amount = 0;
//	std::cin >> seg_amount;
//	int points_amount = seg_amount * 2;
//	int *array = new int[points_amount];
//	for (int i = 0; i < points_amount; i++) {
//		cin >> array[i];
//	}
//
//
//
//	cout << findresult(array, points_amount);
//	delete[] array;
//	return 0;
//}
bool operator < (const Point& l, const Point& r) {
	if (l.X == r.X)
		return l.Delta < r.Delta;
	return l.X < r.X;
}


template <class T, class Compare>
void merge(T* arr, int l, int r, Compare cmp) {
	if (r <= l)
		return;
	if (r - l == 1) {
		if (cmp(arr[r] , arr[l]))
			swap(arr[r], arr[l]);
		return;
	}
	int m = (r + l) / 2;
	merge(arr, l, m, cmp);
	merge(arr, m + 1, r,cmp);
	T *buf = new T[r - l + 1];
	int xl = l;
	int xr = m + 1;
	int cur = 0;
	while (r - l + 1 != cur) {
		if (xl > m)
			buf[cur++] = arr[xr++];
		else if (xr > r)
			buf[cur++] = arr[xl++];
		else if (cmp(arr[xr] , arr[xl]))
			buf[cur++] = arr[xr++];
		else buf[cur++] = arr[xl++];

	}
	for (int i = 0; i < cur; i++)
		arr[i + l] = buf[i];
}
int findresult(int* array, int size) {
	Point* points = new Point[size];
	for (int i = 0; i < size - 1; ) {
		points[i].X = array[i];
		points[i + 1].X = array[i + 1];
		points[i].Delta = 1;
		points[i + 1].Delta = -1;
		i += 2;
	}


	merge(points, 0, size - 1, isLess);
	/*for (int i = 0; i < size; ++i) {
	cout << points[i].X << ' ' << points[i].Delta << endl;
	}*/
	int layers = 0;
	int segs = 0;
	int l = 0;
	int r = 0;
	for (int i = 0; i < size; ++i) {

		if (points[i].Delta == 1) {
			if (layers == 0)
				l = points[i].X;
			layers++;
		}
		else layers--;
		if (layers == 0)
			segs += points[i].X - l;
	}
	delete[] points;
	return segs;
}


int main()
{
	int seg_amount = 0;
	std::cin >> seg_amount;
	int points_amount = seg_amount * 2;
	int *array = new int[points_amount];
	for (int i = 0; i < points_amount; i++) {
		cin >> array[i];
	}
	cout << findresult(array, points_amount);

	return 0;
}
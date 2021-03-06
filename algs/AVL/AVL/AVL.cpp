// AVL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include<assert.h>
using namespace std;
template <class T>
struct AVLNode
{
	T Key;
	int Height;
	int Elems;
	AVLNode* Left;
	AVLNode* Right;
	AVLNode(T key) : Key(key), Height(1), Elems(1), Left(NULL), Right(NULL) {};

};
template <class T>
int Elems(AVLNode<T>* node) {
	return node ? node->Elems : 0;

}
template <class T>
void fixElems(AVLNode<T>* node)
{
	if (!node)
		return;
	unsigned char el = Elems(node->Left);
	unsigned char er = Elems(node->Right);
	node->Elems = el + er + 1;
}
template <class T>
int Height(AVLNode<T>* node) {
	return node ? node->Height : 0;

}
template <class T>
int bfactor(AVLNode<T>* node)
{
	return Height(node->Right) - Height(node->Left);
}
template <class T>
void fixheight(AVLNode<T>* node)
{
	if (!node)
		return;
	unsigned char hl = Height(node->Left);
	unsigned char hr = Height(node->Right);
	node->Height = (hl>hr ? hl : hr) + 1;
}
template <class T>
class AVL
{
public:
	AVL();
	~AVL();
	AVLNode<T>* RightRotate(AVLNode<T>* p);
	AVLNode<T>* LeftRotate(AVLNode<T>* p);
	AVLNode<T>* Add(AVLNode<T>* current, T key);
	bool Remove(AVLNode<T>*& p, T k);
	AVLNode<T>* Balance(AVLNode<T>* p);
	AVLNode<T>* GetRoot() { return root; };
	void DeleteNode(AVLNode<T>* &node);

private:
	AVLNode<T>* root;

};
template <class T>
AVL<T>::AVL() :
	root(NULL)
{
}
template <class T>
AVL<T>::~AVL()
{
	delete root;
}
template <class T>
AVLNode<T>* AVL<T>::LeftRotate(AVLNode<T>* p) {
	AVLNode<T>* q = p->Right;
	p->Right = q->Left;
	q->Left = p;
	fixheight(p);
	fixheight(q);
	fixElems(p);
	fixElems(q);
	return q;
}
template <class T>
AVLNode<T>* AVL<T>::RightRotate(AVLNode<T>* q) {
	AVLNode<T>*p = q->Left;
	q->Left = p->Right;
	p->Right = q;
	fixheight(q);
	fixheight(p);
	fixElems(q);
	fixElems(p);
	return p;
}
template <class T>
AVLNode<T>* AVL<T>::Balance(AVLNode<T>* p) {
	if (!p)
		return NULL;
	fixheight(p);
	fixElems(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->Right) < 0)
			p->Right = RightRotate(p->Right);

		return LeftRotate(p);;
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->Left) > 0)
			p->Left = LeftRotate(p->Left);

		return RightRotate(p);
	}

	return p;
}
template <class T>
AVLNode<T>* AVL<T>::Add(AVLNode<T>* current, T key) {
	if (!root) {
		root = new AVLNode<T>(key);
		return root;
	}
	if (!current) {
		return new AVLNode<T>(key);

	}
	if (key < current->Key)
		current->Left = Add(current->Left, key);
	else
		current->Right = Add(current->Right, key);
	root = Balance(current);
	return root;
}

template <class T>
bool AVL<T>::Remove(AVLNode<T>*& p, T k) // удаление ключа k из дерева p
{
	AVLNode<T>* x;
	if (p == NULL)
		return false;
	if (p->Key == k) {
		//AVLNode<T>* x = p;
		DeleteNode(p);
		x = p;
		p = Balance(x);
		if (p && (p->Left == NULL) && (p->Right == NULL)) cout << "lolkek :(" << endl;
		root = p;
		return true;
	}
	bool res = Remove(p->Key > k ? p->Left : p->Right, k);

	x = p;
	p = Balance(x);
	root = p;
	return res;


}
template <class T>
void AVL<T>::DeleteNode(AVLNode<T>*& node) {
	if (node->Left == 0) { // Если нет левого поддерева.
		AVLNode<T>* right = node->Right; // Подставляем правое, может быть 0.
		delete node;
		node = right;
		node = Balance(node);

	}
	else if (node->Right == 0) { // Если нет правого поддерева.
		AVLNode<T>* left = node->Left; // Подставляем левое.
		delete node;
		node = left;
		node = Balance(node);

	}
	else { // Есть оба поддерева.
		   // Ищем минимальный элемент в правом поддереве и его родителя.
		AVLNode<T>* Parent = node;
		AVLNode<T>* minParent = node;
		AVLNode<T>* min = node->Right;
		while (min->Left != 0) {
			Parent = minParent;
			minParent = min;
			min = min->Left;
		}
		// Переносим значение.
		node->Key = min->Key;
		// Удаляем min, подставляя на его место min->Right.
		(minParent->Left == min ? minParent->Left : minParent->Right)
			= min->Right;

		fixheight(minParent);
		fixElems(minParent);

		delete min;
		if (minParent != node) (Parent->Left == minParent ? Parent->Left : Parent->Right) = Balance(minParent);
		node = Balance(node);

	}



}
template <class T>
T GetKStat(AVLNode<T>* p, int k) {
	assert(k <= Elems(p));
	if (k == Elems(p->Left))
		return p->Key;
	if (k < Elems(p->Left))
		GetKStat(p->Left, k);
	else
	{
		int rightK = k - Elems(p->Left) - 1;
		GetKStat(p->Right, rightK);
	}
}
int main()
{
	AVL<int> tree;
	int n;
	int value;
	int k;
	cin >> n;
	int* array = new int[n * 2];

	for (int i = 0; i < n * 2; i++)
	{
		cin >> value >> k;
		array[i] = value;
		array[++i] = k;
	}
	for (int i = 0; i < n * 2; i++)
	{

		value = array[i];
		k = array[++i];
		if (value < 0) {
			AVLNode<int>* root = tree.GetRoot();
			tree.Remove(root, abs(value));
			cout << GetKStat(root, k) << " ";
		}
		else {
			tree.Add(tree.GetRoot(), value);
			cout << GetKStat(tree.GetRoot(), k) << " ";
		}
	}
	delete[] array;
	return 0;
}
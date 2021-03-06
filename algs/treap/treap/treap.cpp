// treap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

template<class T>
struct TreapNode
{
	T Data;
	int Priority;
	TreapNode* Left;
	TreapNode* Right;
	TreapNode(const T& data, const T& priority) : Data(data), Priority(priority), Left(NULL), Right(NULL) {};
};

template<class T>
void split(TreapNode<T> *currentNode, T data, TreapNode<T> *&left, TreapNode<T> *&right)
{
	if (currentNode == NULL)
	{
		left = NULL;
		right = NULL;
	}
	else if (currentNode->Data <= data)
	{
		split(currentNode->Right, data, currentNode->Right, right);
		left = currentNode;
	}
	else
	{
		split(currentNode->Left, data, left, currentNode->Left);
		right = currentNode;
	}
}

template<class T>
class Treap
{
public:
	Treap() : root(NULL), elemCount(0) {};
	~Treap();
	void Add(const T& key, const T& priority);
	int GetMaxWidth();
	void GetWidth(TreapNode<T> *currentNode, int level, vector<int>& array);
	int GetHeight(TreapNode<T> *currentNode);
	

private:
	TreapNode<T>* root;
	int elemCount;
};

template<class T>
Treap<T>::~Treap()
{
	TreapNode<T>* current = root;
	queue<TreapNode<T>*> q;
	//здесь хранятся ноды в которых уже были


	while (true) {



		if (current->Left) {
			q.push(current->Left);
		}

		if (current->Right)
		{
			q.push(current->Right);
		}
		delete current;
		if (q.empty())
			break;
		current = q.front();

		q.pop();

	}

}

template<class T>
void Treap<T>::Add(const T& key, const T& priority)
{
	TreapNode<T>* newNode = new TreapNode<T>(key, priority);
	if (root == NULL) {
		root = newNode;
		elemCount++;
		return;
	}
	TreapNode<T>* current = root;
	TreapNode<T>* child = root;
	TreapNode<T>* parent = NULL;
		
	while (current && priority < current->Priority){
		
		if (key <= current->Data)
			child = child->Left;
		else
			child = child->Right;
		parent = current;
		current = child;

	}
	split(current, key, newNode->Left, newNode->Right);
	if (parent == NULL) {
		root = newNode;
		return;
	}
		
	if (key < parent->Data)
		parent->Left = newNode;
	else
		parent->Right = newNode;
	elemCount++;
	return;
	
}

template<class T>
void Treap<T>::GetWidth(TreapNode<T> *currentNode, int level, vector<int>& array) {
	array[level]++;
	if (!(currentNode->Left || currentNode->Right))
		return;
	int nextLevel = ++level;
	if (currentNode->Left) {

		GetWidth(currentNode->Left, nextLevel, array);
	}
	if (currentNode->Right)
		GetWidth(currentNode->Right, nextLevel, array);
}

template<class T>
int Treap<T>::GetHeight(TreapNode<T> *currentNode) {

	if (!(currentNode->Left || currentNode->Right))
		return 1;

	int heightLeft = 0;
	int heightRight = 0;

	if (currentNode->Left)
		heightLeft = GetHeight(currentNode->Left);
	if (currentNode->Right)
		heightRight = GetHeight(currentNode->Right);
	return heightLeft > heightRight ? ++heightLeft : ++heightRight;
}

template<class T>
int Treap<T>::GetMaxWidth() {
	int height = GetHeight(root);
	vector<int> layersWidth;
	layersWidth.resize(height, 0);
	GetWidth(root, 0, layersWidth);
	return *max_element(layersWidth.begin(), layersWidth.end());
}



template < class T>
struct BSTNode {
	T Data;
	BSTNode* Left;
	BSTNode* Right;

	BSTNode(const T& data) : Data(data), Left(NULL), Right(NULL) {};
	bool HasChild() {
		return (Left || Right);
	}

};

template < class T>
class BST {
public:
	BST() : root(NULL), elemCount(0) {};
	~BST();
	void Add(const T& data);
	int GetMaxWidth();
	void GetWidth(BSTNode<T> *currentNode, int level, vector<int>& array);
	int GetHeight(BSTNode<T> *currentNode);

private:
	BSTNode<T>* root;
	int elemCount;
};

template < class T>
BST<T>::~BST() {
	BSTNode<T>* current = root;
	queue<BSTNode<T>*> q;//здесь хранятся ноды в которых уже были


	while (true) {



		if (current->Left) {
			q.push(current->Left);
		}

		if (current->Right)
		{
			q.push(current->Right);
		}
		delete current;
		if (q.empty())
			break;
		current = q.front();

		q.pop();

	}


}

template < class T>
void BST<T>::Add(const T& data) {
	BSTNode<T>* newNode = new BSTNode<T>(data);
	if (root == NULL) {
		root = newNode;
		elemCount++;
		return;
	}
	BSTNode<T>* current = root;
	BSTNode<T>* child = root;
	while (child) {
		current = child;
		if (data <= current->Data)
			child = child->Left;
		else
			child = child->Right;

	}


	if (data <= current->Data)
		current->Left = newNode;
	else
		current->Right = newNode;
	elemCount++;
	return;


}

template<class T>
void BST<T>::GetWidth(BSTNode<T> *currentNode, int level, vector<int>& array) {
	array[level]++;
	if (!(currentNode->Left || currentNode->Right))
		return;
	int nextLevel = ++level;
	if (currentNode->Left) {

		GetWidth(currentNode->Left, nextLevel, array);
	}
	if (currentNode->Right)
		GetWidth(currentNode->Right, nextLevel, array);
}

template<class T>
int BST<T>::GetHeight(BSTNode<T> *currentNode) {

	if (!(currentNode->Left || currentNode->Right))
		return 1;

	int heightLeft = 0;
	int heightRight = 0;

	if (currentNode->Left)
		heightLeft = GetHeight(currentNode->Left);
	if (currentNode->Right)
		heightRight = GetHeight(currentNode->Right);
	return heightLeft > heightRight ? ++heightLeft : ++heightRight;
}

template<class T>
int BST<T>::GetMaxWidth() {
	int height = GetHeight(root);
	vector<int> layersWidth;
	layersWidth.resize(height, 0);
	GetWidth(root, 0, layersWidth);
	return *max_element(layersWidth.begin(), layersWidth.end());
}

int main()
{
	Treap<int> treap;
	BST<int> bstTree;
	int size;

	cin >> size;
	for (int i = 0; i < size; i++)
	{
		int key, priority;
		cin >> key >> priority;
		
		treap.Add(key, priority);
		bstTree.Add(key);
	}
	
	cout <<(treap.GetMaxWidth() - bstTree.GetMaxWidth());


	
    return 0;
}


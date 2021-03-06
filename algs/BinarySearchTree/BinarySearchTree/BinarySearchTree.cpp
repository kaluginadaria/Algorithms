// BinarySearchTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
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
	queue<T> PreOrder();


private:
	BSTNode<T>* root;
	int elemCount;
};
template < class T>
BST<T>::~BST() {
	BSTNode<T>* current = root;
	queue<BSTNode<T>*> q;//здесь хранятся ноды в которых уже были
	
	
	while (true) {
		

		
		if (current->Left ) {
			q.push(current->Left);
		}
		
		if (current->Right)
		{
			q.push(current->Right);
		}
		delete current;
		if (q.empty() )
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
template < class T>
queue<T> BST<T>::PreOrder() {
	BSTNode<T>* current = root;
	stack<BSTNode<T>*> stackNodes;//здесь хранятся ноды в которых уже были
	bool isVisited = false;
	queue<T> result;
	while (true) {
		if (!isVisited) { //если еще не выводили
			result.push(current->Data);
		}
		
		if (current->Left && current->Right && !isVisited)
			stackNodes.push(current);
		if (current->Left && !isVisited) {
			current = current->Left;
			continue;
		}
		isVisited = false;
		if (current->Right)
		{
			current = current->Right;
			continue;
		}
		if (stackNodes.empty() && !current->HasChild())
			break;
		current = stackNodes.top();
		isVisited = true;
		stackNodes.pop();
		
	}
	return result;
}


int main()
{
	
	BST<int> tree;
	int commandsCount;
	cin >> commandsCount;
	int elem;
	for (int i = 0; i < commandsCount; i++)
	{
		cin >> elem;
		tree.Add(elem);
	}

	queue<int> q = tree.PreOrder();
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		cout << q.front()<< " ";
		q.pop();
	}

    return 0;
}


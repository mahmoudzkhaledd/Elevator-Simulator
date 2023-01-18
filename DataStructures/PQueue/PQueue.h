#pragma once
#include<bits/stdc++.h>
using namespace std;
template<class Type>
class PQNode
{
public:
	int weight = 0;
	Type data;
	PQNode<Type>* next = NULL;
	PQNode(Type d, int p) {
		data = d;
		weight = p;
	}
};

template<class T>
class PriorityQueue {
	PQNode<T>* front = NULL;
public:
	int count = 0;
	void insert(T val, int weight)
	{
		PQNode<T>* temp, * q;
		temp = new PQNode<T>(val, weight);
		if (front == NULL || weight > front->weight)
		{
			temp->next = front;
			front = temp;
		}
		else
		{
			q = front;
			while (q->next != NULL && q->next->weight >= weight)
				q = q->next;
			temp->next = q->next;
			q->next = temp;
		}
		count++;
	}
	T remove()
	{
		PQNode<T>* temp;
		if (front != NULL)
		{
			temp = front;
			T data = temp->data;
			front = front->next;
			free(temp);
			count--;
			return data;
		}
		return null;
	}
	int size() {
		return count;
	}
	T ElementAt(int i) {
		if (i > count) return NULL;
		PQNode<T>* n = front;
		int c = 0;
		while (n != NULL && c < i) {
			n = n->next;
			c++;
		}
		return n->data;
	}
	void display()
	{
		PQNode<T>* t;
		t = front;
		if (front == NULL)
			printf("Queue is empty\n");
		else
		{
			while (t != NULL)
			{
				cout << t->data << endl;
				t = t->next;
			}
		}
	}
	bool isEmpty() {
		return front == NULL;
	}
};
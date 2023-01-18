#pragma once
#include "../Node.h"

#define null NULL
#include<iostream>
using namespace std;
template <class type>
class Stack {
	Node<type>* top = null;
public:
	void push(type val) {
		if (top == null) {
			top = new Node<type>(val, null);
			return;
		}
		top = new Node<type>(val, top);
	}
	void pop() {
		if (top != null) {
			Node<type>* n = top->next;
			delete top;
			top = n;
		}
	}
};
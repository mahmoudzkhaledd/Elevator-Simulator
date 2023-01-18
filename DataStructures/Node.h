#pragma once
template <class type>
class Node {
public:
	type val;
	Node<type>* next;
	Node(type v, Node<type>* n) {
		val = v;
		next = n;
	}
};
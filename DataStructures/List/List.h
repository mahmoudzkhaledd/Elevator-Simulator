#pragma once
#include "../Node.h"
#define null NULL
#include<iostream>
#include<vector>
using namespace std;
template <typename T>
class List {
	vector<T> v;
	/*Node<T>* head = null;
	Node<T>* tail = null;*/
public:
	int count = 0;
	T LastElement() {
		//return l[l.size()-1];
		//return tail->val;
		return null;
	}
	T ElementAt(int index) {
		return v[index];
		/*Node<T>* n = head;
		while (index--) {
			n = n->next;
		}
		return n->val;*/
	}
	void insert(T val) {
		v.push_back(val);
		count++;
		/*if (head == null) {
			head = tail = new Node<T>(val, null);
		}
		else {
			tail->next = new Node<T>(val, null);
			tail = tail->next;
		}
		count++;*/
	}
	void insertIn(T val, int index) {
		/*if (index > count) return;
		if (index == 0) {
			head = new Node<T>(val, head);
			count++;
		}
		else {
			int c = 0;
			Node<T>* t = head;
			while (t != null) {
				if (c + 1 == index) {
					Node<T>* n = t->next;
					t->next = new Node<T>(val, n);
					count++;
					break;
				}
				c++;
				t = t->next;
			}
		}*/
	}
	void Delete(T &val) {
		for (int i = 0; i < v.size(); i++) {
			if(v[i] == val){
				v.erase(v.begin() + i);
				count--;
				return;
			}
		}
		/*if (head != null && head->val == val) {
			Node<T>* a = head->next;
			delete head;
			head = a;
			count--;
			return;
		}
		Node<T>* prev = null;
		Node<T>* t = head;
		while (t != null) {
			prev = t;
			t = t->next;
			if (t != null && t->val == val) {
				prev->next = t->next;
				delete t;
				count--;
				break;
			}
		}*/
	}
	void DeleteAt(int index) {
		/*if (index > count || index < 0)
			return;
		if (head != null && index == 0) {
			Node<T>* a = head->next;
			delete head;
			head = a;
			count--;
			return;
		}
		int c = 0;
		Node<T>* prev = null;
		Node<T>* t = head;
		while (t != null) {
			prev = t;
			t = t->next;
			if (t != null && c + 1 == index) {
				prev->next = t->next;
				delete t;
				count--;
				break;
			}
			c++;
		}*/
	}
};

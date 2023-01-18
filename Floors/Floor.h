#pragma once
#include"../DataStructures/List/List.h"
#include<iostream>
struct Directions
{
	List<int> up;
	List<int> down;
};
class Floor {
public:
	Floor* next;
	Floor* prev;



	Directions pWaiting;

	Directions vWaiting;

	Directions cWaiting;



	int index;
	
	Floor(int i, Floor* n = NULL, Floor* p = NULL) 
	{ index = i; next = n; prev = p; }
};
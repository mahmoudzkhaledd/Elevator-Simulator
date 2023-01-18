#pragma once
#include"../Main_Elevator.h"
class P_Elevator :public Elevator {
public:
	P_Elevator() :Elevator() { type = 'P'; }
	
};
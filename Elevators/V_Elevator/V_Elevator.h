#pragma once
#include"../Main_Elevator.h"
class V_Elevator :public Elevator {
public:
	V_Elevator() :Elevator() {
		type = 'V';
	}
	

};
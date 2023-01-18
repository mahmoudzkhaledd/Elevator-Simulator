#pragma once
#include "../Passenger.h"
class Patient : public Pickable {
public:
	int EMR_Level;
	Patient(int id, int tim, int emr, Floor* src, Floor* trg);
};
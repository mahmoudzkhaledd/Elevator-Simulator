#pragma once
#include "../Passenger.h"
class Cargo : public Pickable {
public:
	Cargo(int id, int tim , Floor* src, Floor* trg);
};
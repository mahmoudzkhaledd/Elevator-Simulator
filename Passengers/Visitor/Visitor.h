#pragma once
#include "../Passenger.h"
class Visitor : public Pickable {
public:
	Visitor(int id, int tim, Floor* src, Floor* trg);
};
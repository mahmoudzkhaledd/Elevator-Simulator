#include "Passenger.h"

Pickable::Pickable(PassengerType t, int id,int tim, Floor* src, Floor* trg)
	:type(t),ID(id), eventTime(tim), currentFloor(src), targetFloor(trg) 
{
	if (targetFloor->index > currentFloor->index)
		direction = UP;
	else direction = Down;
}
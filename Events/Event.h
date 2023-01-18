#pragma once

#include "../Passengers/Cargo/Cargo.h"
#include "../Passengers/Patient/Patient.h"
#include "../Passengers/Visitor/Visitor.h"

class Event {
public:
	Floor* ground;
	int eventTime = 0;
	Pickable* item;
	char type;

	virtual void ExecuteEvent();
};

class ArrivalEvent: public Event {
public:
	PassengerType passType;
	
	
	int ID;
	int srcFloor;
	int targetFloor;
	int emrLevel;


	ArrivalEvent(PassengerType t, int id, int eT, int srcF, int targF, int emrL);
	void ExecuteEvent();
};

class LeaveEvent : public Event {
public:
	int ID;
	LeaveEvent(int eT, int id);
	void ExecuteEvent();
};

class StairsEvent : public Event {
public:
	int ID;
	StairsEvent(int eT, int id);
	void ExecuteEvent();
};

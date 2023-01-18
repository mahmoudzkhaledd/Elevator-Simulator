#pragma once
#include "../Passengers/Passenger.h"
#include"../Floors/Floor.h"
#include "../Events/Event.h"

enum ElevatorState
{
	IDLE,
	MOVEUP, 
	MOVEDOWN,
	UNLOAD,
	AVAIL,
	OUT
};

class Elevator { 
public:

	List<Pickable*> passengers;



	List<Event*> requests;





	Floor* currentFloor;
	Floor* targetFloor;
	int idleTime = 3;
	int waitingTime = 9;



	int currentCapacity;
	



	char type = 'P';




	ElevatorState state;

	Elevator();
	bool done();
	void moveUP();
	void moveDown();
	static void deleteFromFloor(Pickable* pass);

	void deleteRequest(Pickable* p);
	void setState(ElevatorState s);
	void Request(Event* f);
	bool Load(Pickable* pass);
	bool checkState();
	void checkForPassengers();
	void timeChange();
};


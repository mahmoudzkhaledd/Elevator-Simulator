#pragma once
#include"../Floors/Floor.h"

enum PassengerType {
	P_Pass = 'P',
	V_Pass = 'V',
	C_Pass = 'C'
};
enum Direction {
	UP,
	Down
};
class Pickable {
public:
	int ID;
	int eventTime;
	int pickTime = 0;
	int targetTime = 0;
	int waitingTime = 0;
	int serviceTime = 0;
	Floor* currentFloor;

	Floor* targetFloor;

	const PassengerType type;
	Direction direction;
	

	Pickable(PassengerType t, int id, int tim,Floor* src, Floor* trg);
};
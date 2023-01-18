#pragma once
#include<string>
#include"../Hospital/Hospital.h"
using namespace std;

class UI { 
	Hospital* hospital;
public:
	UI(Hospital* h) {
		hospital = h;
		hospital->loadData();
		startScreen();
	}
	int getInt(string mesage, string errMess);
	int getIntBetween(string mesage, string errMess,int s,int e);

	void printPatients(Floor* f);
	void printCargos(Floor* f);
	void printVisitors(Floor* f);
	void printElevators(Floor* f);

	string getState(ElevatorState s);

	void interactiveMode();
	void startScreen();
	void testMode();
	void stepByStepMode();
	void silentMode();
};
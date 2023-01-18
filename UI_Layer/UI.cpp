#include <iostream>
#include <cstdio>
#include<string>

#include "UI.h"
#include "../DataStructures/List/List.h"
#include"../File_Layer/Data.h"
using namespace std;

int UI::getInt(string mesage, string errMess = "") {
	string s = "";
	while (1) {
		cout << mesage;
		cin >> s;
		bool err = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] > '9' || s[i] < '0') {
				err = 1;
				mesage = errMess != "" ? errMess : mesage;
			}
		}
		if (!err) break;
	}
	return stoi(s);
}

int UI::getIntBetween(string mesage, string errMess, int start, int end) {
	string s = "";
	int number;
	while (1) {
		cout << mesage;
		cin >> s;
		bool err = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] > '9' || s[i] < '0') {
				err = 1;
				mesage = errMess != "" ? errMess : mesage;
			}
		}
		if (!err) {
			number = stoi(s);
			if (number >= start && number <= end)
				break;
			else
				mesage = errMess;
		}
	}
	return stoi(s);
}

void UI::printPatients(Floor* f)
{
	cout << f->pWaiting.up.count + f->pWaiting.down.count
		<< " Waiting Patients: UP[";
	for (int i = 0; i < f->pWaiting.up.count; i++) {
		cout << f->pWaiting.up.ElementAt(i);
		if (i != f->pWaiting.up.count - 1) {
			cout << ",";
		}
	}
	cout << "] ";
	cout << "Down [";
	for (int i = 0; i < f->pWaiting.down.count; i++) {
		cout << f->pWaiting.down.ElementAt(i);
		if (i != f->pWaiting.down.count - 1) {
			cout << ",";
		}
	}
	cout << "] " << endl;
}

void UI::printCargos(Floor* f)
{
	cout << f->cWaiting.up.count + f->cWaiting.down.count
		<< " Waiting Cargo: UP[";
	for (int i = 0; i < f->cWaiting.up.count; i++) {
		cout << f->cWaiting.up.ElementAt(i);
		if (i != f->cWaiting.up.count - 1) {
			cout << ",";
		}
	}
	cout << "] ";
	cout << "Down [";
	for (int i = 0; i < f->cWaiting.down.count; i++) {
		cout << f->cWaiting.down.ElementAt(i);
		if (i != f->cWaiting.down.count - 1) {
			cout << ",";
		}
	}
	cout << "] " << endl;
}

void UI::printVisitors(Floor* f)
{
	cout << f->vWaiting.up.count + f->vWaiting.down.count
		<< " Waiting Visitors: UP[";
	for (int i = 0; i < f->vWaiting.up.count; i++) {
		cout << f->vWaiting.up.ElementAt(i);
		if (i != f->vWaiting.up.count - 1) {
			cout << ",";
		}
	}
	cout << "] ";
	cout << "Down [";
	for (int i = 0; i < f->vWaiting.down.count; i++) {
		cout << f->vWaiting.down.ElementAt(i);
		if (i != f->vWaiting.down.count - 1) {
			cout << ",";
		}
	}
	cout << "] ";
}
string UI::getState(ElevatorState s)
{
	string state =
		(s == IDLE) ? "IDLE" :
		(s == MOVEUP) ? "Move Up" :
		(s == MOVEDOWN) ? "Move Down" :
		(s == UNLOAD) ? "Unload" : "Available";
	return state;
}
void UI::printElevators(Floor* f)
{
	if (hospital->pElevator->currentFloor == f) {
		cout << endl << endl << "P Elevator<" << getState(hospital->pElevator->state) << "> " << "[";
		for (int i = 0; i < hospital->pElevator->passengers.count; i++) {
			Pickable* p = hospital->pElevator->passengers.ElementAt(i);
			cout << "ID: " << p->ID << " Floor: " << p->currentFloor->index;
			if (i != hospital->pElevator->passengers.count - 1)
				cout << " , ";
		}
		cout << "]";
	}
	if (hospital->vElevator->currentFloor == f) {
		cout << endl << endl << "V Elevator<" << getState(hospital->vElevator->state) << "> " << "[";
		for (int i = 0; i < hospital->vElevator->passengers.count; i++) {
			Pickable* p = hospital->vElevator->passengers.ElementAt(i);
			cout << "ID: " << p->ID << " Floor: " << p->currentFloor->index;
			if (i != hospital->vElevator->passengers.count - 1)
				cout << " , ";
		}
		cout << "]";
	}
	if (hospital->cElevator->currentFloor == f) {
		cout << endl << endl << "C Elevator<" << getState(hospital->cElevator->state) << "> " << "[";
		for (int i = 0; i < hospital->cElevator->passengers.count; i++) {
			Pickable* p = hospital->cElevator->passengers.ElementAt(i);
			cout << "ID: " << p->ID << " Floor: " << p->currentFloor->index;
			if (i != hospital->cElevator->passengers.count - 1)
				cout << " , ";
		}
		cout << "]";
	}
}

void UI::startScreen() {
	int ch = 1;
	cout << "			Welcome to elevator simulator"
		<< endl
		<< "Please enter the number of the selected mode:"
		<< "\n	1-Interactive Mode\n	2-Step-By-Step Mode\n	3-Silent Mode\n";

	while (1) {
		ch = getIntBetween("Your choice: "
			, "Error, Please enter a valid number between 1 and 3: "
			, 1, 3);
		if (ch > 0 && ch <= 3)
			break;
	}
	switch (ch)
	{
	case 1:
		interactiveMode();
		break;
	case 2:
		stepByStepMode();
		break;
	case 3:
		silentMode();
		break;
	default:
		break;
	}
	Data d;
	d.OutputFile();
}

void UI::testMode() {
	system("cls");

	while (1) {
		hospital->nextTimeStep();
		cout << "current Time step: " << hospital->currentTime<<" [";
		for (int i = 0; i < hospital->pElevator->requests.count; i++) {
			Pickable* p = hospital->pElevator->requests.ElementAt(i)->item;
			cout << "ID: " << p->ID << " Floor: " << p->currentFloor->index<<" -> "
				 <<p->targetFloor->index;
			if (i != hospital->pElevator->requests.count - 1)
				cout << " , ";
		}
		cout << "]" << endl;
		string state = 
			(hospital->pElevator->state ==IDLE)?"IDLE":
			(hospital->pElevator->state == MOVEUP)?"Move Up":
			(hospital->pElevator->state == MOVEDOWN)?"Move Down":
			(hospital->pElevator->state == UNLOAD)?"Unload":"Available";
		cout << "P Elevator<" << state << ">: " << hospital->pElevator->currentFloor->index << " [";
		for (int i = 0; i < hospital->pElevator->passengers.count; i++) {
			Pickable* p = hospital->pElevator->passengers.ElementAt(i);
			cout <<"ID: "<<p->ID<<" Floor: " << p->currentFloor->index;
			if (i != hospital->pElevator->passengers.count - 1)
				cout << " , ";
		}
		cout << "]" << endl;
		cout << "-------------------------------------------" << endl;
		cin.get();
	}
}

void UI::interactiveMode() {
	while (!hospital->done()) {
		hospital->nextTimeStep();
		cout << "Current timestep: " << hospital->currentTime << endl << endl;
		Floor* f = hospital->topFloor;
		while (f != null) {
			printPatients(f);
			printCargos(f);
			printVisitors(f);
			printElevators(f);
			cout << endl << "--------------------- Floor "
				<< f->index << " ---------------------" << endl << endl;
			f = f->prev;
		}
	}
}

void UI::stepByStepMode() {
	system("cls");
	cin.ignore();
	while (!hospital->done()) {
		hospital->nextTimeStep();
		cout << "Current timestep: " << hospital->currentTime << endl << endl;
		Floor* f = hospital->topFloor;
		while (f != null) {
			printPatients(f);
			printCargos(f);
			printVisitors(f);
			printElevators(f);
			cout << endl << "--------------------- Floor "
				<< f->index << " ---------------------" << endl << endl;
			f = f->prev;
		}
		cin.get();
		system("cls");
	}
}

void UI::silentMode() {
	cout << "Silent Mode" << endl;
	cout << "Start Simulating..." << endl;
	while (!hospital->done()) {
		hospital->nextTimeStep();
	}
	cout << "Done.";
}

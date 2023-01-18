#include "Event.h"
#include "../Hospital/Hospital.h"
#include <math.h>
#include<iostream>
using namespace std;

ArrivalEvent::ArrivalEvent(PassengerType t,int id,int eT, int srcF, int targF, int emrL = 0) {
	ID = id;
	passType = t; 
	eventTime = eT;
	srcFloor = srcF; 
	targetFloor = targF; 
	emrLevel = emrL;
	type = 'A';
}

void ArrivalEvent::ExecuteEvent() {
	Floor* s = NULL;
	Floor* t = NULL;
	Floor* tmp = Hospital::ground;
	
	for (int i = 0; i <= Hospital::info.floors; i++) {
		if (i == srcFloor)
			s = tmp;
		if (i == targetFloor)
			t = tmp;
		if (s != NULL && t != NULL)
			break;
		tmp = tmp->next; 
	}

	if (passType == P_Pass) {
		item = new Patient(ID,eventTime, emrLevel, s, t);
		if (item->direction == UP)
			s->pWaiting.up.insert(ID);
		else
			s->pWaiting.down.insert(ID);
	}
	else if (passType == V_Pass) {
		item = new Visitor(ID,eventTime, s, t);
		Hospital::totalTisitors++;
		if (item->direction == UP)
			s->vWaiting.up.insert(ID);
		else
			s->vWaiting.down.insert(ID);
	}
	else if (passType == C_Pass){
		item = new Cargo(ID, eventTime, s, t); 
		if (item->direction == UP)
			s->cWaiting.up.insert(ID);
		else
			s->cWaiting.down.insert(ID);
	}

	Hospital::pass.insert(item);

	cout << "A " << char(item->type) << " " << item->eventTime << " " << item->ID
		<< " " << item->currentFloor->index 
		<< " " << item->targetFloor->index 
		<< " " << endl;
}


LeaveEvent::LeaveEvent(int eT, int id) {
	eventTime = eT;
	ID = id;
	type = 'L';
}

void LeaveEvent::ExecuteEvent()
{
	for (int i = 0; i < Hospital::pass.count; i++) {
		Pickable* p = Hospital::pass.ElementAt(i);
		if (p->ID == ID){
			item = p;
			Hospital::Leave.insert(item);
			Hospital::pass.Delete(p);
			Elevator::deleteFromFloor(p);
			cout << "L " << eventTime << " " << p->ID << endl;
			break;
		}
	}
	// Execute
}

StairsEvent::StairsEvent(int eT, int id)
{
	eventTime = eT;
	ID = id;
	type = 'S';
}

void StairsEvent::ExecuteEvent()
{
	for (int i = 0; i < Hospital::pass.count; i++) {
		Pickable* p = Hospital::pass.ElementAt(i);
		if (p->ID == ID) {
			item = p;
			Hospital::stairs.insert(item);
			Hospital::pass.Delete(item);
			Elevator::deleteFromFloor(p);
			cout << "S " << eventTime << " " << item->ID << endl;
			break;
		}
	}
	// Execute
}

void Event::ExecuteEvent(){}
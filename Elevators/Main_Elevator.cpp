#include"Main_Elevator.h"
#include "../Hospital/Hospital.h"
#include<list>
using namespace std;
Elevator::Elevator() {
	currentCapacity = 0;
	state = IDLE;
	currentFloor = Hospital::ground;
	targetFloor = null;
}

bool Elevator::done() {
	return (passengers.count == 0) && (requests.count == 0);
}

void Elevator::moveUP() {
	if (currentFloor->next != null) {
		state = MOVEUP;
		currentFloor = currentFloor->next;
		for (int i = 0; i < passengers.count; i++) {
			Pickable* p = passengers.ElementAt(i);
			p->currentFloor = currentFloor;
		}
	}
}

void Elevator::moveDown()
{
	if (currentFloor->prev != null) {
		state = MOVEDOWN;
		currentFloor = currentFloor->prev;
		for (int i = 0; i < passengers.count; i++) {
			Pickable* p = passengers.ElementAt(i);
			p->currentFloor = currentFloor;
		}
	}
}

void Elevator::deleteFromFloor(Pickable* pass) // delete the passenger from his floor 
{
	if (pass->type == V_Pass) {
		if (pass->direction == UP)
			pass->currentFloor->vWaiting.up.Delete(pass->ID);
		else
			pass->currentFloor->vWaiting.down.Delete(pass->ID);
	}
	else if (pass->type == P_Pass) {
		if (pass->direction == UP)
			pass->currentFloor->pWaiting.up.Delete(pass->ID);
		else
			pass->currentFloor->pWaiting.down.Delete(pass->ID);
	}
	else if (pass->type == C_Pass) {
		if (pass->direction == UP)
			pass->currentFloor->cWaiting.up.Delete(pass->ID);
		else
			pass->currentFloor->cWaiting.down.Delete(pass->ID);
	}
}

bool Elevator::Load(Pickable* pass) {
	if (Hospital::info.cCap < currentCapacity + 1)
		return false;
	if (type == 'C') {
		for (int i = 0; i < passengers.count; i++) {
			Pickable* pic = passengers.ElementAt(i);
			if (pass->type == C_Pass && pic->type != C_Pass)
				return false;
			if (pass->type != C_Pass && pic->type == C_Pass)
				return false;
		}
		passengers.insert(pass);
		Hospital::pass.Delete(pass);
		deleteFromFloor(pass);
		return true;
	}
	else {
		int cap = (type == 'P') ? Hospital::info.pCap : Hospital::info.vCap;
		if (pass->type == C_Pass && cap < currentCapacity + 1)
			return false;

		Hospital::pass.Delete(pass);
		passengers.insert(pass);
		deleteFromFloor(pass);
	}
	pass->pickTime = Hospital::currentTime;
	currentCapacity++;
	pass->waitingTime = pass->pickTime - pass->eventTime;
	return true;
}

bool Elevator::checkState() {
	if (state != IDLE) {
		if (requests.count == 0 && passengers.count == 0) {
			if (waitingTime > 0) {
				waitingTime--;
				return true;
			}
			else {
				setState(IDLE);
				return false;
			}
		}
		else {
			setState(AVAIL);
			return true;
		}
	}
	else {
		if (idleTime > 0 && requests.count > 0 && passengers.count <= 0) {
			idleTime--;
			return false;
		}
		else {
			if ((requests.count > 0 || passengers.count > 0) && idleTime <= 0) {
				setState(AVAIL);
				return true;
			}
			else {
				setState(IDLE);
				return false;
			}
		}
	}
}

void Elevator::deleteRequest(Pickable* p){
	if (p != null) {
		for (int i = 0; i < requests.count; i++) {
			Event* e = requests.ElementAt(i);
			if (e->item->ID == p->ID) {
				requests.Delete(e);
				break;
			}
		}
	}
}

void Elevator::setState(ElevatorState s) {
	state = s;
	waitingTime = 9;
	idleTime = 3;
}

bool between(int num, int f, int s) {
	return (num >= f && num <= s);
}

void Elevator::checkForPassengers() {
	/*
		checks for any passengers in the elevator to unload or any passenger on the current floor to load them
	*/
	int passBeforeUnload = passengers.count;
	for (int i = 0; i < passengers.count; i++) { // check for passengers to unload
		Pickable* p = passengers.ElementAt(i);
		if (p->targetFloor == currentFloor) {
			p->currentFloor = currentFloor;
			passengers.Delete(p);
			currentCapacity--;
			i--;
			p->targetTime = Hospital::currentTime;
			p->serviceTime = p->targetTime - p->pickTime;
			Hospital::completed.insert(p,p->targetTime);
			state = UNLOAD;
		}
	}
	if (passBeforeUnload > passengers.count && passengers.count == 0) {
		setState(IDLE);
		return;
	}
	for (int i = 0; i < requests.count; i++) { // check for passengers to load
		Event* e = requests.ElementAt(i);
		bool dir = true;
		if (targetFloor != null) {
			
			int pTarget = e->item->targetFloor->index;

			int eTarget = targetFloor->index;


			if (state == MOVEUP && 
				e->item->direction == UP && 
				pTarget <= eTarget) {
				dir = true;
			}
			else if (state == MOVEDOWN 
				&& e->item->direction == Down 
				&& pTarget >= eTarget) {
				dir = true;
			}
			/*else if (state == MOVEDOWN 
				&& e->item->direction == Down 
				&& pTarget <= eTarget) {
				dir = true;
			}*/
			else dir = false;
			
			if (targetFloor == currentFloor) dir = true;
		}

		if ((e->item->currentFloor == currentFloor) && dir) {
			state = AVAIL;
			if (Load(e->item)) {
				requests.Delete(e);
				i--;
			}
		}
	}
}

void Elevator::timeChange() {
	int speed = (type == 'V') ? Hospital::info.vSpeed
		: (type == 'P') ? Hospital::info.pSpeed
		: Hospital::info.cSpeed;


	if (Hospital::currentTime % speed == 0) {
		if (requests.count > 0 && passengers.count == 0) { // the elevator is empty and there is requests
			Pickable* pi = requests.ElementAt(0)->item;

			int fl = pi->currentFloor->index;

			if (fl > currentFloor->index) {
				moveUP();
				targetFloor = pi->currentFloor;
			}
			else if (fl < currentFloor->index) {
				moveDown();
				targetFloor = pi->currentFloor;
			}

			checkForPassengers();
			return;
		}
		
		Pickable* p = (passengers.count == 0) ? null : passengers.ElementAt(0);

		if (p != null) { // there is passengers in the elevator 

			if (p->targetFloor->index > currentFloor->index) {
				moveUP();
				targetFloor = p->targetFloor;
			}
			else if (p->targetFloor->index < currentFloor->index) {
				moveDown();
				targetFloor = p->targetFloor;
			}

			checkForPassengers();
		}
	}
}

void Elevator::Request(Event* e) {
	requests.insert(e);


	/*if (req.find(e->item->currentFloor->index) == req.end()) {
		List<Event*> l;
		l.insert(e);
		int f = e->item->currentFloor->index;
		req.insert({ f, l });
	}
	else req[e->item->currentFloor->index].insert(e);*/
}

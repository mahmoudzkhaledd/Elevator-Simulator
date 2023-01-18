#include"Hospital.h"
#include "../Elevators/Main_Elevator.h"
#include "../File_Layer/Data.h"


Info Hospital::info = Info();
int Hospital::currentTime = -1;
Floor* Hospital::ground = NULL;
Floor* Hospital::topFloor = NULL;
List<Pickable*> Hospital::pass = List<Pickable*>();
PriorityQueue<Pickable*> Hospital::completed = PriorityQueue<Pickable*>();
List<Pickable*> Hospital::stairs = List<Pickable*>();
int Hospital::autoStairs = 0;
int Hospital::totalTisitors = 0;

List<Pickable*> Hospital::Leave = List<Pickable*>();



Hospital::Hospital() {
	ground = topFloor = NULL;
	currentTime = -1;
}

int Hospital::countFloors() { // Test Function only 
	int i = 0;
	Floor* f = ground;
	while (f != null) {
		f = f->next;
		i++;
	}
	return i;
}


void Hospital::createElevators() {
	Hospital::pElevator = new P_Elevator();
	Hospital::cElevator = new C_Elevator();
	Hospital::vElevator = new V_Elevator();
}


void Hospital::loadData() {
	Data file;
	events = file.loadDataFromFile("Data.txt"); // Load Data From the input file

	createFloors(); // create the floors

	createElevators(); // initilize the elevators

}
void Hospital::checkVisitors() {
	for (int i = 0; i < pass.count; i++) {
		Pickable* p = Hospital::pass.ElementAt(i);
		if (p->type == V_Pass) {
			if (currentTime - p->eventTime == info.autoS) {
				autoStairs++;
				
				Autoostairs.insert(p);
				pElevator->deleteRequest(p);
				vElevator->deleteRequest(p);
				cElevator->deleteRequest(p);

				Elevator::deleteFromFloor(p);

				pass.Delete(p);
				cout << p->ID << " AutoS" << endl;
			}
		}
	}
}
void Hospital::nextTimeStep() {
	currentTime++;

	loadRequest();

	checkVisitors();


	if (pElevator->checkState()) {
		pElevator->checkForPassengers();
		pElevator->timeChange(); 
		// tell the elevator to move on spacific direction or not to move
	}

	if (vElevator->checkState()) {
		vElevator->checkForPassengers();
		vElevator->timeChange();
	}
	if (cElevator->checkState()) {
		cElevator->checkForPassengers();
		cElevator->timeChange();
	}
}
void Hospital::createFloors() {
	for (int i = 0; i < info.floors; i++) {
		if (ground == null) {
			ground = new Floor(i, null);
			topFloor = ground;
		}
		else {
			topFloor->next = new Floor(i, null,topFloor);
			topFloor = topFloor->next;
		}
	} 
}


void Hospital::makeRequest(PriorityQueue<Event*> pq) {
	while (!pq.isEmpty()) {
		Event* e = pq.remove();
		if (e->item->type == P_Pass) {
			if (pElevator->currentCapacity < info.pCap)
 				pElevator->Request(e);
			else if (vElevator->currentCapacity < info.vCap)
				vElevator->Request(e);
			else
				cElevator->Request(e);
		}
		else if (e->item->type == C_Pass) {
			if (cElevator->currentCapacity < info.cCap) 
				cElevator->Request(e);
		}
		else if (e->item->type == V_Pass) {	
			if (vElevator->currentCapacity < info.vCap) {
				vElevator->Request(e);
			}	
			else {
				pElevator->Request(e);
			}
		}
	}
}
void Hospital::loadRequest() {
	PriorityQueue<Event*> pq;

	while (!events.isEmpty() && events.Front()->eventTime == currentTime) {
		Event* e = events.Dequeue();
		if (e != null) {
			
			e->ExecuteEvent();
			if (e->type != 'A') {
				Pickable* p = e->item;
				pElevator->deleteRequest(p);
				vElevator->deleteRequest(p);
				cElevator->deleteRequest(p);
			}
			if (e->type == 'A') {
				
				int weight = 0;

				if (e->item->type == P_Pass) 
					weight = ((Patient*)e->item)->EMR_Level + abs(((Patient*)e->item)->targetFloor - ((Patient*)e->item)->currentFloor);
				else if (e->item->type == C_Pass) 
					weight = -1;
				else
					weight = -2;

				pq.insert(e,weight);
			}
		} 
	}

	if(pq.count > 0)
		makeRequest(pq);
}

bool Hospital::done()
{
	bool eve = events.isEmpty();
	return eve && pElevator->done() && vElevator->done() && cElevator->done();
}

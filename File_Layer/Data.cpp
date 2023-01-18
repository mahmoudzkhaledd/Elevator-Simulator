#include "Data.h"
#include "../Elevators/Main_Elevator.h"
#include"../Passengers/Cargo/Cargo.h"
#include"../Passengers/Patient/Patient.h"
#include"../Passengers/Visitor/Visitor.h"

#include<string>
#include<iostream>
#include <fstream>
using namespace std;

Queue<Event*> Data::loadDataFromFile(string filePath = "") {
	ifstream stream;
	int count = 0;
	stream.open(filePath);

	stream >> Hospital::info.floors
		>> Hospital::info.vSpeed
		>> Hospital::info.cSpeed
		>> Hospital::info.pSpeed
		>> Hospital::info.vCap
		>> Hospital::info.cCap
		>> Hospital::info.pCap
		>> Hospital::info.vCheck
		>> Hospital::info.cCheck
		>> Hospital::info.pCheck 
		>> Hospital::info.S 
		>> Hospital::info.autoS
		>> count;

	PriorityQueue<PriorityQueue<Event*>*> p;
	
	PriorityQueue<Event*>* tmp = null;

	int time = -1;

	for (int i = 0; i < count; i++) {
		char eventType;
		stream >> eventType; 
		if (eventType == 'A') {
			int weight = -1;

			char pT;
			int ET, ID, SRCF, TRGF, EMR = 0;

			stream >> pT >> ET >> ID >> SRCF >> TRGF;

			if (pT == 'P') {
				stream >> EMR;
				weight = EMR + abs(TRGF - SRCF);
			}
			PassengerType typ = (pT == 'P') 
				? P_Pass : (pT == 'V') 
				? V_Pass : C_Pass;

			if (time != ET) {

				tmp = new PriorityQueue<Event*>();

				p.insert(tmp, -ET);

				tmp->insert(new ArrivalEvent(typ, ID, ET, SRCF, TRGF, EMR), weight);
				time = ET;

			}
			else {
				tmp->insert(new ArrivalEvent(typ, ID, ET, SRCF, TRGF, EMR), weight);
			}
			int x = p.size();
			int z = p.ElementAt(p.size() - 1)->size();
			int m = p.size();
			//events.insert(new ArrivalEvent(typ, ID, ET, SRCF, TRGF, EMR),weight);
		}
		else {
			int ET, ID;
			stream >> ET >> ID;
			
			if (eventType == 'L') {
				if (time != ET) {
					tmp = new PriorityQueue<Event*>();
					p.insert(tmp, -ET);
					tmp->insert(new LeaveEvent(ET, ID), 0);
				}
				else {
					tmp->insert(new LeaveEvent(ET, ID), 0);
				}
				//events.insert(new LeaveEvent(ET, ID));
			}
			else if (eventType == 'S') {
				if (time != ET) {
					tmp = new PriorityQueue<Event*>();
					p.insert(tmp,-ET);
					tmp->insert(new StairsEvent(ET, ID), 0);
				}
				else {
					tmp->insert(new StairsEvent(ET, ID), 0);
				}
				//events.insert(new StairsEvent(ET, ID));
			}
		}
	}
	stream.close();



	Queue<Event*> events;
	while (!p.isEmpty()) {
		PriorityQueue<Event*>* pq = p.remove();
		while (!pq->isEmpty())
			events.EnQueue(pq->remove());
	}
	return events;
}

void Data::OutputFile() {
	PriorityQueue<Pickable*> l = Hospital::completed;
	ofstream os;
	os.open("output.txt");
	os << "TT	ID	AT	WT	ST" << endl;
	int patient = 0;
	int visitor = 0;
	int cargo = 0;
	int numWait = 0;
	int sumWait = 0;

	int numServe = 0;
	int sumServe = 0;
	while (!l.isEmpty())
	{
		Pickable* p = l.remove();
		os << p->targetTime << "	"
			<< p->ID << "	"
			<< p->eventTime << "	"
			<< p->waitingTime << "	"
			<< p->serviceTime << endl;
		if (p->type == 'P')patient++;
		else if (p->type == 'V') visitor++;
		else if (p->type == 'C') cargo++;
		numWait++;
		sumWait += p->waitingTime;
		numServe++;
		sumServe += p->serviceTime;
	}
	double x = (sumWait * 1.0) / (numWait * 1.0);
	double y = (sumServe * 1.0) / (numServe * 1.0);

	os << "Passengers: " << patient + visitor
		<< " [V:" << visitor << ", "
		<< "P: " << patient << "]" << endl << "Cargos: " << cargo << endl;
	os << "AVG Wait = " << x<<endl;
	os << "AVG Serv = " << y<<endl;
	os << "AutoS = " << (Hospital::autoStairs * 1.0 / Hospital::totalTisitors * 1.0)*100 <<"%" << endl;

	os.close();
}


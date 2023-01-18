#pragma once
#include "../Events/Event.h"
#include"../DataStructures/PQueue/PQueue.h"
#include"../DataStructures/List/List.h"
#include"../DataStructures/Queue/Queue.h"
#include"../Floors/Floor.h"
#include "../Elevators/Main_Elevator.h"
#include "../Elevators/C_Elevator/C_Elevator.h"
#include "../Elevators/P_Elevator/P_Elevator.h"
#include "../Elevators/V_Elevator/V_Elevator.h"

struct Info {
	int pCap;
	int vCap;
	int cCap;

	int pSpeed;
	int vSpeed;
	int cSpeed;

	int pCheck;
	int vCheck;
	int cCheck;

	int floors;
	int S;
	int autoS;
	Info() {
		pCap = vCap = cCap = pSpeed = vSpeed = cSpeed = pCheck = vCheck = cCheck = floors = S = autoS = 0;
	}
};
 
class Hospital { 
public:
	static Info info;

	static List<Pickable*> pass;

	static PriorityQueue<Pickable*> completed;
	static List<Pickable*> stairs;
	static int autoStairs;
	static int totalTisitors;
	static List<Pickable*> Leave;

	List<Pickable*> Autoostairs;
	static Floor* ground;

	static Floor* topFloor;

	
	P_Elevator* pElevator;
	C_Elevator* cElevator;
	V_Elevator* vElevator;

	
	static int currentTime; 
	bool done();


	Queue<Event*> events;



	void loadData();
	
	void nextTimeStep();
	void checkVisitors();
	void createFloors();
	void createElevators();
	int countFloors();
	
	void makeRequest(PriorityQueue<Event*> pq);
	void loadRequest();
	
	
	Hospital();
};
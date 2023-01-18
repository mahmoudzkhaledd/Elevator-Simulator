#include<iostream>
#include "DataStructures/List/List.h"
#include "DataStructures/PQueue/PQueue.h"
#include "DataStructures/Queue/Queue.h"
#include "DataStructures/Stack/Stack.h"
#include "Elevators/Main_Elevator.h"
#include "File_Layer/Data.h"
#include "UI_Layer/UI.h"
#include "Hospital/Hospital.h"
using namespace std;

int main() {
	UI(new Hospital());
}
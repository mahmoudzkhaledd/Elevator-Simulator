#pragma once
#include "../Events/Event.h"
#include"../Hospital/Hospital.h"
#include "../DataStructures/PQueue/PQueue.h"
#include "../DataStructures/List/List.h"
#include"../DataStructures/Queue/Queue.h"
using namespace std;
class Data {
public:
	Queue<Event*> loadDataFromFile(string filePath);
	void OutputFile();
};
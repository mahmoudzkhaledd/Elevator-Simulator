#include"Patient.h"
Patient::Patient(int id, int tim, int emr, Floor* src, Floor* trg)
	:Pickable(P_Pass, id ,tim,src,trg) { EMR_Level = emr; }
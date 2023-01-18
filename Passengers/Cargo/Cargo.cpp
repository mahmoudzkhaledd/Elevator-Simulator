#include"Cargo.h"
Cargo::Cargo(int id, int tim, Floor* src, Floor* trg)
	:Pickable(C_Pass, id, tim, src, trg) {}
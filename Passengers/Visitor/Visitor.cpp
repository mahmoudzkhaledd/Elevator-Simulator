#include "Visitor.h"
Visitor::Visitor(int id, int tim, Floor* src, Floor* trg)
	:Pickable(V_Pass,id,tim,src,trg) {}
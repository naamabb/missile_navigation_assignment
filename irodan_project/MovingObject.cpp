#include "MovingObject.h"

void MovingObject::move(double timeStep)
{
	location = location + direction * speed* timeStep;
	
}

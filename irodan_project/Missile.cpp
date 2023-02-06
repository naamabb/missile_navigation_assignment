#include "Missile.h"


float Missile::move(double timeStep)
{
	//calculate Acceleration
	
	Vector2f missileNext, targetNext, delta, d;

	//min of  (V_new - V_old).norm(),  aMax*TimeStep (V_new - V_old).normalize()*(a_max)*TimeStep + v_old
	double distance = calculateDistance(target);
	double time = distance / speed;
	targetNext = target->location + target->direction * speed * time*timeStep;
	missileNext = location + direction * speed * timeStep;
	d =  targetNext - missileNext ;
	delta = d - direction;
	
	
	if (delta.norm() > aMax * timeStep) {
		direction = delta.normalized() * aMax * timeStep + direction;
	}
	else {
		direction = d.normalized();
	}

	location = location + direction * speed * timeStep;
	return delta.norm();

}

double Missile::calculateDistance(MovingObject* other) {
	double x_t = other->location.x(), y_t = other->location.y();
	return std::sqrt(std::pow(x_t - location.x(), 2) + std::pow(y_t - location.y(), 2));
}

int Missile::findTarget(std::vector<MovingObject*>& objects) {
	int obj = -1;
	double distance, curDistance;
	int i = 0;
	for (auto o : objects) {
		if (o->status) {
			curDistance = calculateDistance(o);
			if (obj == -1 || curDistance < distance) {
				obj = i;
				distance = curDistance;
			}
		}
		i++;
	}
	target = objects[obj];
	//direction = (target->location - location).normalized();
	return obj;
}

bool Missile::checkCollision(MovingObject* other, double dk) {
	return calculateDistance(other) < dk;

}

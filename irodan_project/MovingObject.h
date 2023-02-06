#pragma once
#include "eigen-3.3.9/Eigen/Dense"
#include <cmath>
#include <vector>
#include <stdio.h>
#include <iostream>

constexpr double pi = 3.14159265358979323846;
#define LIVE 1
#define HIT 0
using Eigen::Vector2f;

class MovingObject
{
public:
	Vector2f direction, location;
	float speed;
	int index;
	bool status;
	MovingObject(float x, float y, double ang, float v, int i) {
		location <<x, y;
		double radians =  pi * ang / 180;
		direction << cos(radians), sin(radians); // ang must be in radians
		speed = v;
		index = i;
		status = LIVE;


	}
	void move(double timeStep);





};


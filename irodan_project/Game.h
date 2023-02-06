#pragma once

#include "MovingObject.h"
#include "Missile.h"
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>

#define KILL_ORIG_OBJ "#########target destroyed############"
#define KILL_RAND_OBJ "#########random object destroyed#####"
#define DEFINE_TARGET "#########finds the nearest target####"
#define REPORT 3

struct History {
public:
	std::string msg;
	int objectIndex;
	Vector2f location, missile_location;
	double time;
};

class Game
{

private:
	double mTimeStep, mMissileStartTime, mKillDistance, mTime;
	int mNumberOfObjects;
	std::vector<MovingObject*> mLiveObjects, allObjects;
	std::vector<struct History*> mGameHistory;
	Missile* missile;
	

	void gameLoop(std::ostream& logf);

public:
	Game(double t, double ts):mTimeStep(t),mMissileStartTime(ts), mKillDistance(0), mNumberOfObjects(0),mTime(0){}
	void addObject(float x, float y, float ang, float v);
	void setKillDistance(double dk);
	void addMissile(float xm, float ym, float vm, double aMax);
	void startGame(std::ostream& , std::ostream& );//
	void addHistoryEvent(std::string msg, int index, Vector2f loc, Vector2f m_loc, double t);




};


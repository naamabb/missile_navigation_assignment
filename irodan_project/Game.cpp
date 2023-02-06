#include "Game.h"

void Game::addObject(float x, float y, float ang, float v) {
	mLiveObjects.push_back(new MovingObject(x, y, ang, v,mNumberOfObjects));
	mNumberOfObjects++;
}
void Game::setKillDistance(double dk)
{
	mKillDistance = dk;
	
}
void Game::addMissile(float xm, float ym, float vm, double aMax) {
	missile = new Missile(xm, ym, vm, aMax);
}
void Game::startGame(std::ostream& historyf, std::ostream& eventf) {
	mTime = 0;
	std::cout << "call game loop" << std::endl;
	gameLoop(eventf);
	for (auto h : mGameHistory) {
		historyf << h->msg << "\t" << std::endl;
		historyf << "time " << h->time <<": \n" << "object number: " << h->objectIndex << " at location: " <<
			h->location.x() << ", " << h->location.y() << std::endl;
		historyf <<"missile location: "<< h->missile_location.x() << ", " << h->missile_location.y()<< std::endl;
	}
	std::cout << "game over" << std::endl;



}

void Game::addHistoryEvent(std::string msg, int index, Vector2f loc,Vector2f m_loc, double t) {
	struct History* h = new struct History();
	h->msg = msg;
	h->objectIndex = index;
	h->location = loc;
	h->missile_location = m_loc;
	h->time = t;
	mGameHistory.push_back(h);
}

void Game::gameLoop(std::ostream& logf) {
	std::cout << "start game loop" << std::endl;
	float lateral_acc = 0;
	int interval = 0;
	int live = mNumberOfObjects;
	while (live > 0) {
		interval++;
		bool findNewTar = false;
		mTime += mTimeStep;

		if ((interval%REPORT == 0)&& (mTime > mMissileStartTime)) {
				logf << "time: " << mTime << std::endl;
				logf << "missile parameter - location, direction, lateral acceleration: " << std::endl;
				logf << "(" << missile->location.x() << ", " << missile->location.y()<<")" << ", " << 
					"(" << missile->direction.x() << ", " << missile->direction.y() << ")" << ", " << lateral_acc << std::endl;
				logf << "-----------------------------" << std::endl;


		}

		
		if (std::abs(mTime - mMissileStartTime) < 0.001) {
			std::cout << "missile is on" << std::endl;
			int i = missile->findTarget(mLiveObjects);
			MovingObject* t = mLiveObjects[i];
			addHistoryEvent(DEFINE_TARGET, t->index, t->location,missile->location, mTime);
		}

		if (mTime > mMissileStartTime) {
			lateral_acc = missile->move(mTimeStep);
			
		}
		
		
		int length = mLiveObjects.size();
		for (int i = 0; i < length; i++) {
			MovingObject* o = mLiveObjects[i];
			if (interval%REPORT == 0) {
				logf << "time: " << mTime << std::endl;
				logf << "object number " << o->index << " - location, status(live = 1, hit= 0): \n" <<"("<< o->location.x() << ", " << o->location.y() << ")" << ", " << o->status << std::endl;
				logf << "-----------------------------" << std::endl;
			}
			if (o->status == HIT) {
				continue;
			}
			if (mTime > mMissileStartTime) {
				if (missile->checkCollision(o, mKillDistance)) {
					live--;
					o->status = HIT;
					if (o->index == missile->target->index) {
						addHistoryEvent(KILL_ORIG_OBJ, o->index, o->location, missile->location, mTime);
						if (live) {
							int j = missile->findTarget(mLiveObjects);
							MovingObject* t = mLiveObjects[j];
							addHistoryEvent(DEFINE_TARGET, t->index, t->location, missile->location, mTime);
						}
					}
					else {
						addHistoryEvent(KILL_RAND_OBJ, o->index, o->location, missile->location, mTime);
					}
					
					

				}
				else {
					o->move(mTimeStep);
				}
			}

		}
		

	}
	
}

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cout << "missing config file." << std::endl;
		return 1;
	}
	std::ifstream config(argv[1]);
	if (!config) {
		std::cout << "fail to open file: " << argv[1] << std::endl;
		return 1;
	}
	double t, ts, dk;//time step, missile start, killing distance
	int n; //number of objects.
	float x, y, ang,v; // object location x y , direction angle.
	config >> t;
	config >> ts;
	config >> n;
	Game* g = new Game(t, ts);
	for (int i = 0; i < n; i++) {
		config >> x;
		config >> y;
		config >> ang;
		config >> v;
		g->addObject(x, y, ang, v);
	}
	float xm, ym, vm;
	double aMax;
	config >> xm;
	config >> ym;
	config >> vm;
	config >> aMax;
	g->addMissile(xm, ym, vm, aMax);
	config >> dk;
	g->setKillDistance(dk);
	std::ofstream eventFile("events.txt", std::ios::trunc);
	std::ofstream historyFile("history.txt", std::ios::trunc);
	if (eventFile && historyFile) {
		g->startGame(historyFile, eventFile);
	}
	else {
		std::cout << "error in opening files" << std::endl;
		return 1;
	}
}

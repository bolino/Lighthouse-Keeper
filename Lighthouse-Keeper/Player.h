#pragma once
#include "SDL_opengl.h"
#include "Forest.h"
#include "Wolf.h"
#include "SDL_mixer.h" 
#include <list>

class Wolf;

class Player
{
public:
	Player(void);
	~Player(void);

	void render();
	void update(double dt);

	float getX();
	float getY();

	void setTexture(GLuint t);
	void setTrees(std::list<Forest*> f) {trees = f;}
	void setWolfs(std::list<Wolf*> w) {wolfs = w;}

	void damage();
	int getHealth() {return health;}
	int getFuel() {return fuel;}
	void setHealth(int h) {health = h;}
	void setFuel(int f) {fuel = f;}
	void setX(int px) {x = px;}
	void setY(int py) {y = py;}

private:
	float frameDT;
	float actionDT;
	int frame;
	float x;
	float y;
	int speed;
	int fuel;
	int action; //0 idle, 1 walking, 2 get fuel, 3 attack
	std::list<Forest*> trees;
	std::list<Wolf*> wolfs;
	GLuint texture;
	float checkCollisions();
	void harvest();
	int health;
	void attack();
	float attackDT;
	int typeHarvested; //0 for pine, 1 for oil
	Forest* treeHarvested;
	void playSound(Mix_Chunk *sound);
	Mix_Chunk *harvestSound;
	Mix_Chunk *fuelSound;
};

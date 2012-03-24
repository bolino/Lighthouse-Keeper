#pragma once
#include "SDL_opengl.h"
#include "Player.h" 
#include "SDL_mixer.h"

class Player;

class Wolf
{
public:
	Wolf(Player* p);
	~Wolf(void);

	void update(double dt, float playerx, float playery);
	void render();
	void setTexture(GLuint t);
	float getX() {return x;}
	float getY() {return y;}
	int getHealth() {return health;}
	void damage();

private:
	GLuint texture;
	float x;
	float y;
	int frame;
	float frameDT;
	int action; //0 wandering, 1 attacking
	int dir; //direction it's moving, 0 left, 1 right
	float walkDT;
	float walkTicks;
	bool isPlayerNear(float radio, float playerx, float playery);
	void attack();
	Player* player;
	float attackDT;
	int health;
	void playSound(Mix_Chunk *sound);
	Mix_Chunk *damageSound;
	Mix_Chunk *attackSound;
};

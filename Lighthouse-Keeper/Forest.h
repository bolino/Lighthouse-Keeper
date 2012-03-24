#pragma once
#include "SDL_opengl.h"

class Forest
{
public:
	Forest(void);
	Forest(int t, float posx, float posy);
	~Forest(void);

	void update();
	void render();
	void setTexture(GLuint t);
	void setCut(GLuint t);
	int harvest();
	float getX() {return x;}
	float getY() {return y;}
	int getType() {return type;}
	int getFuel() {return fuel;}
private:
	int type; //0 pine, 1 olives, 3 cut
	float x;
	float y;
	GLuint texture;
	GLuint textureCut;
	int fuel;
};

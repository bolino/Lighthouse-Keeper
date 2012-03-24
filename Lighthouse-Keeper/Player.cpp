#include "Player.h"
#include "Input.h"
#include <iostream>
#include <math.h>

Player::Player(void)
{
	x = 140;
	y = 400;
	speed = 50;
	fuel = 0;
	frame = 0;
	frameDT = 0;
	action = 0;
	health = 3;
	attackDT = 0;
	harvestSound = Mix_LoadWAV("cut.wav");
	fuelSound = Mix_LoadWAV("fuel.wav");
	treeHarvested = NULL;
}

Player::~Player(void)
{
}

void Player::render()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x,y,0);

	glColor3f(1,1,1);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	glTexCoord2f(0.25f + frame*0.25f,1);
	glVertex2f(8,16);
	glTexCoord2f(0.25f + frame*0.25f,0);
	glVertex2f(8,-16);
	glTexCoord2f(frame*0.25f,0);
	glVertex2f(-8,-16);
	glTexCoord2f(frame*0.25f,1);
	glVertex2f(-8,16);

	glEnd();

	//action bar
	if (action == 2)
	{
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,0,0);
		glBegin(GL_LINES);
		glVertex2f(-8,-20);
		glVertex2f(8*actionDT,-20);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		
	}

	glPopMatrix();
}

void Player::update(double dt)
{	
	attackDT -= dt;

	if (action != 2)
	{
		if (Input::isKeyPressed(KEY_UP))
		{
			y -= speed*dt;
			action = 1;
		}
		if (Input::isKeyPressed(KEY_LEFT))
		{
			x -= speed*dt;
			action = 1;
		}
		if (Input::isKeyPressed(KEY_DOWN))
		{
			y += speed*dt;
			action = 1;
		}
		if (Input::isKeyPressed(KEY_RIGHT))
		{
			x += speed*dt;
			action = 1;
		}
		if (Input::isKeyPressed(KEY_A))
		{
			harvest();
		}
		if (Input::isKeyPressed(KEY_S))
		{
			if (attackDT <= 0)
			{
				attack();
				attackDT = 0.25f;
			}
		}
	}

	checkCollisions();

	if (action == 1)
	{
		frameDT += dt;

		if (frameDT >= 0.25f)
		{
			frameDT = 0;
			frame = ++frame % 4;
		}
		action = 0;
	}
	else if (action == 2)
	{
		actionDT += dt;

		if (treeHarvested->getType() == 0)
		{
			if (actionDT >= 1.0f)
			{
				action = 0;
				fuel += treeHarvested->harvest();

				if (treeHarvested->getFuel() <= 0)
					playSound(fuelSound);
				std::cout << fuel << std::endl;
			}
		}
		else
		{
			if (actionDT >= 1.5f)
			{
				action = 0;
				fuel += treeHarvested->harvest();

				if (treeHarvested->getFuel() <= 0)
					playSound(fuelSound);
				std::cout << fuel << std::endl;
			}
		}
	}
	else
	{
		frame = 0;
	}
}

float Player::getX()
{
	return x;
}

float Player::getY()
{
	return y;
}

void Player::setTexture(GLuint t)
{
	texture = t;
}

float Player::checkCollisions()
{
	std::list<Forest*>::iterator treeIT;

	for (treeIT=trees.begin(); treeIT != trees.end(); treeIT++)
	{
		if ((*treeIT)->getType() != 3)
		{
			float treex = (*treeIT)->getX();
			float treey = (*treeIT)->getY();

			if (x <= treex + 40 && x >= treex - 40)
				if (y <= treey + 48 && y >= treey - 48)
				{
					float diffX = 0;
					float diffY = 0;

					if (abs(x - (treex  + 40)) > abs(x - (treex - 40)))
					{
						diffX = abs(x - treex + 40);
						diffX *= -1;
					}
					else
					{
						diffX = abs(x - treex - 40);
						
					}

					if (abs(y - (treey  + 48)) > abs(y - (treey - 48)))
					{
						diffY = abs(y - treey + 48);
						diffY *= -1;
					}
					else
					{
						diffY = abs(y - treey - 48);
					}

					if (abs(diffX) < abs(diffY))
					{
						x += diffX;
						return diffX;
					}
					else
					{
						y += diffY;
						return diffY;
					}
				}
		}
	}

	if (x < 140)
		x = 140;
	return 0;
}

void Player::harvest()
{
	std::list<Forest*>::iterator treeIT;

	for (treeIT=trees.begin(); treeIT != trees.end(); treeIT++)
	{
		if ((*treeIT)->getType() != 3)
		{
			float treex = (*treeIT)->getX();
			float treey = (*treeIT)->getY();

			if (x <= treex + 40 && x >= treex - 40)
				if (y <= treey + 48 && y >= treey - 48)
				{
					action = 2;
					frame = 0;
					actionDT = 0;
					treeHarvested = (*treeIT);
					typeHarvested = (*treeIT)->getType();
					playSound(harvestSound);
					break;
				}
		}
	}
}

void Player::damage()
{
	health--;
}

void Player::attack()
{
	std::list<Wolf*>::iterator wolfIT;

	for (wolfIT=wolfs.begin(); wolfIT!= wolfs.end(); wolfIT++)
	{
			Wolf* w = (*wolfIT);
			float diffX = x - w->getX();
			float diffY = y - w->getY();
			diffX *= diffX;
			diffY *= diffY;

			if (diffX + diffY <= 1100)
			{
				w->damage();
			}
		//chequear si el lobo esta cerca, si esta atacar, fijarse si se murio y si lo hizo sacarlo de la lista
	}
}

void Player::playSound(Mix_Chunk *sound)
{
	if(sound == NULL) 
	{
		std::cout << Mix_GetError() << std::endl;
	}
	int channel = Mix_PlayChannel(-1, sound, 0);
}
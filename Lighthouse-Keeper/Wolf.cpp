#include "Wolf.h"
#include <stdlib.h>
#include <iostream>

Wolf::Wolf(Player* p)
{
	x = 215 + (rand() % 367);
	y = 225 + (rand() % 255);
	frame = 0;
	frameDT = 0;
	action = 0;
	dir = rand() % 2;
	walkDT = 0;
	walkTicks = rand() % 5;
	player = p;
	attackDT = 0;
	health = 2;
	damageSound = Mix_LoadWAV("attack.wav");
	attackSound = Mix_LoadWAV("wolfattack.wav");
}

Wolf::~Wolf(void)
{
}

void Wolf::update(double dt, float playerx, float playery)
{
	frameDT += dt;
	if (frameDT >= 0.25f)
	{
		frame = (++frame % 2);
		frameDT = 0;
	}

	if (action == 0)
	{
		attackDT -= dt;
		if (dir == 0)
		{
			x -= (rand() % 30) * dt;
			if (x < 215)
			{
				x = 215;
				dir = 1;
			}
		} else if (dir == 1)
		{
			x += (rand() % 30) * dt;
			if (x > 582)
			{
				x = 582;
				dir = 0;
			}

		}

		walkDT += dt;
		
		if (walkDT >= walkTicks)
		{
			walkTicks = rand() % 5;
			walkDT = 0;
		}

		if (isPlayerNear(10000, playerx, playery) == true)
		{
			if (attackDT <= 0)
			{
				attackDT = 0;
				action = 1;
			}
		}
		
	}
	else if (action == 1)
	{
		if (playerx - x > 0)
		{
			x += (40 + (rand() % 20)) * dt;
			dir = 1;
		}
		else 
		{
			x -= (40 + (rand() % 20)) * dt;
			dir = 0;
		}

		if (playery - y > 0)
		{
			y += (40 + (rand() % 20)) * dt;
		}
		else 
		{
			y -= (40 + (rand() % 20)) * dt;
		}

		if (isPlayerNear(1000, playerx, playery) == true)
		{
			attack();
			action = 0;
			attackDT = 0.5f;
		}
	}
}

void Wolf::render()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);

	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	
	if (dir == 0)
		glTexCoord2f(0.5f + frame*0.5f,1);
	else
		glTexCoord2f(0 + frame*0.5f,1);
	glVertex2f(16,8);
	if (dir == 0)
		glTexCoord2f(0.5f + frame*0.5f,0);
	else
		glTexCoord2f(0 + frame*0.5f,0);
	glVertex2f(16,-8);
	if (dir == 0)
		glTexCoord2f(0 + frame*0.5f,0);
	else 
		glTexCoord2f(0.5f + frame*0.5f,0);
	glVertex2f(-16,-8);
	if (dir == 0)
		glTexCoord2f(0 + frame*0.5f,1);
	else
		glTexCoord2f(0.5f + frame*0.5f,1);
	glVertex2f(-16,8);

	glEnd();

	glPopMatrix();
}

void Wolf::setTexture(GLuint t)
{
	texture = t;
}

bool Wolf::isPlayerNear(float radio, float playerx, float playery)
{
	float diffX = playerx - x;
	float diffY = playery - y;
	diffX *= diffX;
	diffY *= diffY;

	if (diffX + diffY <= radio)
	{
		return true;
	}
	return false;
}

void Wolf::attack()
{
	if (rand() % 2 == 0)
	{
		player->damage();
		playSound(attackSound);
	}
}

void Wolf::damage()
{
	health--;
	playSound(damageSound);
}

void Wolf::playSound(Mix_Chunk *sound)
{
	if(sound == NULL) 
	{
		std::cout << Mix_GetError() << std::endl;
	}
	int channel = Mix_PlayChannel(-1, sound, 0);
}
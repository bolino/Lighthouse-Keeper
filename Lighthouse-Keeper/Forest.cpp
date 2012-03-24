#include "Forest.h"
#include <stdlib.h>

Forest::Forest(void)
{
	type = 0;
	x = 400;
	y = 200;
	fuel = 10;
}

Forest::Forest(int t, float posx, float posy)
{
	type = t;
	x = posx;
	y = posy;
	fuel = (rand() + 10) % 31;
}

Forest::~Forest(void)
{
}

int Forest::harvest()
{
	fuel -= 10;

	if (type == 0)
	{
		return 10;
	}
	else if (type == 1)
	{
		return 20;
	}
	else
		return 0;
}

void Forest::update()
{
	if (fuel <= 0)
		type = 3;
}

void Forest::render()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);

	glColor3f(1,1,1);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	
	if (type != 3) 
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex2f(32,32);
		glTexCoord2f(1,0);
		glVertex2f(32,-32);
		glTexCoord2f(0,0);
		glVertex2f(-32,-32);
		glTexCoord2f(0,1);
		glVertex2f(-32,32);
	}
	else 
	{
		glBindTexture(GL_TEXTURE_2D, textureCut);
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex2f(16,16);
		glTexCoord2f(1,0);
		glVertex2f(16,0);
		glTexCoord2f(0,0);
		glVertex2f(-16,0);
		glTexCoord2f(0,1);
		glVertex2f(-16,16);
	}

	glEnd();

	glPopMatrix();
}

void Forest::setTexture(GLuint t)
{
	texture = t;
}

void Forest::setCut(GLuint t)
{
	textureCut = t;
}
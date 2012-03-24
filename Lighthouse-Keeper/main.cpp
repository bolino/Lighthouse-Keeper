#include <iostream>
#include "SDL_opengl.h"
#include "Player.h"
#include "Timer.h"
#include "Input.h" 
#include "Wolf.h"
#include "Forest.h"
#include "SDL_mixer.h"
#include <string>
#include <list>
#include <time.h>
#include <stdio.h>
#include <string>

void init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Error intializing sdl" << std::endl;

	if (SDL_SetVideoMode(800, 600, 32, SDL_OPENGL) == NULL)
		std::cout << "Error in setvideomode" << std::endl;

	SDL_WM_SetCaption("Lighthouse Keeper - LD22", NULL);
	
	glEnable(GL_TEXTURE_2D);
	glClearColor(0,0.2f,1,0);
	glLineWidth(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (glGetError() != GL_NO_ERROR)
		std::cout << "Error intializing opengl" << std::endl;

	srand(time(NULL));
}

int island[20][20] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};
GLuint texLighthouse;
GLuint texFuel;
GLuint texGrass;
GLuint texRocks;
GLuint texWater;
GLuint texHeart;
GLuint texTitle;
GLuint texNumbers;
std::list<Wolf*> wolfs;
std::list<Forest*> trees;
Player* player;
GLuint texWolf;
GLuint texPlayer;
GLuint texTree;
GLuint texPine;
GLuint texOlive;
GLuint texCut;

void setup()
{
	//put some wolfs in
	
	Wolf* w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	w = new Wolf(player);
	w->setTexture(texWolf);
	wolfs.push_back(w);
	
	//put some trees in
	
	Forest* t = new Forest(0, 300, 300);
	t->setTexture(texPine);
	t->setCut(texCut);
	trees.push_back(t);
	t = new Forest(0, 350, 320);
	t->setTexture(texPine);
	t->setCut(texCut);
	trees.push_back(t);
	t = new Forest(0, 330, 260);
	t->setTexture(texPine);
	t->setCut(texCut);
	trees.push_back(t);
	t = new Forest(0, 330, 500);
	t->setTexture(texPine);
	t->setCut(texCut);
	trees.push_back(t);
	t = new Forest(0, 380, 520);
	t->setTexture(texPine);
	t->setCut(texCut);
	trees.push_back(t);
	t = new Forest(1, 600, 230);
	t->setTexture(texOlive);
	t->setCut(texCut);
	trees.push_back(t);
	t = new Forest(1, 580, 260);
	t->setTexture(texOlive);
	t->setCut(texCut);
	trees.push_back(t);
	

	player->setTrees(trees);
	player->setWolfs(wolfs);
	player->setX(140);
	player->setY(400);
}

void render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texWater);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(0,0);
	glTexCoord2f(10,0);
	glVertex2f(800,0);
	glTexCoord2f(10,10);
	glVertex2f(800,600);
	glTexCoord2f(0,10);
	glVertex2f(0,600);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texGrass);
	for (int x=0; x < 20; x++)
		for (int y=0; y < 20; y++)
		{
			if (island[x][y] == 1)
			{
				glPushMatrix();
				glLoadIdentity();

				glTranslatef(400 + x*22 - y*22,150 + y*11 + x*11,0);
				//glColor3f(0.5f,1,0.1f);

				/*if ((x+y) % 2 == 0)
					glColor3f(0,0.5f,0.2f);
				else 
					glColor3f(0,0.8f,0.3f);*/

				glScalef(1,0.5,0);
				glRotatef(45,0,0,1);
				
				glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(16,16);
				glTexCoord2f(1,0);
				glVertex2f(16,-16);
				glTexCoord2f(0,0);
				glVertex2f(-16,-16);
				glTexCoord2f(0,1);
				glVertex2f(-16,16);
				glEnd();
				glPopMatrix();
			}
		}
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(80,250,0);
	glBindTexture(GL_TEXTURE_2D, texLighthouse);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-64,-128);
	glTexCoord2f(1,0);
	glVertex2f(64,-128);
	glTexCoord2f(1,1);
	glVertex2f(64,128);
	glTexCoord2f(0,1);
	glVertex2f(-64,128);
	glEnd();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texRocks);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(300, 80, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0.9f);
	glVertex2f(-32,32);
	glTexCoord2f(1,0.9f);
	glVertex2f(32,32);
	glTexCoord2f(1,0);
	glVertex2f(32,-32);
	glTexCoord2f(0,0);
	glVertex2f(-32, -32);
	glEnd();
	glPopMatrix();
}

void loadTexture(const std::string filename, GLuint* textureID) 
{
	SDL_Surface *surface;
	GLenum texture_format;
	GLint  nOfColors;

	if (surface = SDL_LoadBMP(filename.c_str())) 
	{ 
		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
				if (surface->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
				else
						texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
				if (surface->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
				else
						texture_format = GL_BGR;
		} else 
		{
			std::cout << "Error loading texture" << std::endl;
		}
	 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, textureID);
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, *textureID);
	 
		// Set the texture's stretching properties
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
						  texture_format, GL_UNSIGNED_BYTE, surface->pixels );

		if ( surface ) { 
			SDL_FreeSurface( surface );
		}

	} 
	else 
	{
		std::cout << "Error loading texture" << std::endl;
	}
}

void renderNumber(int n)
{
	glBindTexture(GL_TEXTURE_2D, texNumbers);
	glBegin(GL_QUADS);
	glTexCoord2f(0+ n*0.1f,0);
	glVertex2f(0,0);
	glTexCoord2f(0.1f+ n*0.1f,0);
	glVertex2f(8,0);
	glTexCoord2f(0.1f + n*0.1f,1);
	glVertex2f(8,8);
	glTexCoord2f(0+ n*0.1f,1);
	glVertex2f(0,8);
	
	glEnd();
}

void renderHud(int hearts, int fuel, float time)
{
	glColor3f(1,1,1);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(10, 10, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texFuel);
	
	glBegin(GL_QUADS);

	glTexCoord2f(0,0);
	glVertex2f( 10, 10);
	glTexCoord2f(1,0);
	glVertex2f(74,  10);
	glTexCoord2f(1,1);
	glVertex2f( 74, 42);
	glTexCoord2f(0,1);
	glVertex2f( 10,  42);


	glEnd();

	glTranslatef(300,10,0);
	glBindTexture(GL_TEXTURE_2D,texHeart);

	for (int i=0; i<hearts; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex2f( -8 + i*16, -8);
		glTexCoord2f(1,0);
		glVertex2f(8 + i*16,  -8);
		glTexCoord2f(1,1);
		glVertex2f( 8 + i*16, 8);
		glTexCoord2f(0,1);
		glVertex2f( -8 + i*16,  8);
		glEnd();
		glTranslatef(20,0,0);
	}

	//fuel
	glLoadIdentity();
	glTranslatef(70,30,0);

	int fuelNumber = fuel / 100;
	renderNumber(fuelNumber);
	glTranslatef(10,0,0);
	fuelNumber = (fuel % 100) / 10;
	renderNumber(fuelNumber);
	glTranslatef(10,0,0);
	fuelNumber = (fuel % 10);
	renderNumber(fuelNumber);
	glDisable(GL_TEXTURE_2D);
	//time
	if (time <= 60.0f)
	{
		float width = 80 * ((60-time)/60);

			
		glLoadIdentity();
		glTranslatef(500,20,0);
		glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex2f(0,0);
		glVertex2f(width,0);
		glVertex2f(width,8);
		glVertex2f(0,8);
		glEnd();
	}

	glPopMatrix();
	glColor3f(1,1,1);

}

enum STATE {
	title = 0,
	playing,
	gameover,
};

void playSound(Mix_Chunk *sound)
{
	if(sound == NULL) 
	{
		std::cout << Mix_GetError() << std::endl;
	}
	int channel = Mix_PlayChannel(-1, sound, 0);
}



int main(int argc, char* argv[])
{
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		std::cout << Mix_GetError() << std::endl;
	}
	
	Timer timer;
	Input input;
	player = new Player();

	init();
	input.init();
	bool running = true;
	STATE state = title;
	timer.start();
	int ticks = timer.getTicks();
	int lastTicks = timer.getTicks();
	double dt;
	double totalTime = 0;

	//load sounds
	Mix_Chunk *waveSound = NULL;
	waveSound = Mix_LoadWAV("wave.wav");
	Mix_Chunk *gameoverSound = NULL;
	gameoverSound = Mix_LoadWAV("gameover.wav");

	//load textures

	loadTexture("macaco.bmp", &texPlayer);
	GLuint texNofuel;
	loadTexture("nofuel.bmp", &texNofuel);
	GLuint texDead;
	loadTexture("dead.bmp", &texDead);
	GLuint texWin;
	loadTexture("win.bmp", &texWin);
	player->setTexture(texPlayer);
	
	loadTexture("tree.bmp", &texTree);

	loadTexture("wolf.bmp", &texWolf);

	loadTexture("tree.bmp", &texPine);
	
	loadTexture("tree2.bmp", &texOlive);
	loadTexture("treecut.bmp", &texCut);
	loadTexture("lighthouse.bmp", &texLighthouse);
	loadTexture("fuel.bmp", &texFuel);
	loadTexture("grass.bmp", &texGrass);
	loadTexture("rocks.bmp", &texRocks);
	loadTexture("water.bmp", &texWater);
	loadTexture("heart.bmp", &texHeart);
	loadTexture("titlescreen.bmp", &texTitle);
	loadTexture("numbers.bmp", &texNumbers);
	
	setup();

	//iterators
	std::list<Forest*>::iterator treeIT;
	std::list<Wolf*>::iterator wolfIT;

	while(running)
	{
		ticks = timer.getTicks();
		dt = (ticks - lastTicks) / 1000.0;

		input.update();
		if (input.checkQuit() == true)
				running = false;

		if (state == playing)
		{
			totalTime += dt;

			//update
			player->update(dt);

			for (treeIT=trees.begin(); treeIT != trees.end(); treeIT++)
				(*treeIT)->update();
			for (wolfIT=wolfs.begin(); wolfIT!= wolfs.end(); wolfIT++)
			{
				(*wolfIT)->update(dt, player->getX(), player->getY());
			}

			//check if any wolfs are dead
			for (wolfIT=wolfs.begin(); wolfIT!= wolfs.end(); wolfIT++)
			{
				if ((*wolfIT)->getHealth() <= 0)
				{
					wolfs.erase(wolfIT);
					player->setWolfs(wolfs); //not sure if this is needed x_x
					break;
				} 
			}
			
			if (player->getHealth() <= 0)
			{
				playSound(gameoverSound);
				state = gameover;
			}
			if (totalTime >= 60)
			{
				playSound(gameoverSound);
				state = gameover;
			}

			if (Input::isMousePressed())
			{
				int x = (Input::getMouseX() + Input::getMouseY()*2 - 700) / 44;
				int y = (100 - Input::getMouseX() + Input::getMouseY()*2) / 44;
				//std::cout << x  << " " << y << std::endl;
				//std::cout << (-28 + Input::getMouseY()) / 22 << " " << Input::getMouseY() << std::endl;
			}

			

			//render
			glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();
			
			render();
			for (wolfIT=wolfs.begin(); wolfIT!= wolfs.end(); wolfIT++)
				(*wolfIT)->render();
			for (treeIT=trees.begin(); treeIT != trees.end(); treeIT++)
				(*treeIT)->render();
			
			player->render();
			renderHud(player->getHealth(), player->getFuel(), totalTime);
			
			SDL_GL_SwapBuffers();
			lastTicks = ticks;
		}
		else if (state == title)
		{
			if (Input::isKeyPressed(KEY_SPACE))
			{
				state = playing;
				playSound(waveSound);
			}

			glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texTitle);
			glBegin(GL_QUADS);

			glTexCoord2f(0,0);
			glVertex2f( 0, 0);
			glTexCoord2f(1,0);
			glVertex2f(800,  0);
			glTexCoord2f(1,1);
			glVertex2f( 800, 600);
			glTexCoord2f(0,1);
			glVertex2f( 0,  600);


			glEnd();
			SDL_GL_SwapBuffers();
		}
		else if (state == gameover)
		{
			if (player->getHealth() <= 0)
			{
				if (Input::isKeyPressed(KEY_SPACE))
				{
					state = playing;
					playSound(waveSound);
					wolfs.clear();
					trees.clear();
					setup();
					player->setHealth(3);
					player->setFuel(0);
					totalTime = 0;
					
				}

				glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texDead);
				glBegin(GL_QUADS);

				glTexCoord2f(0,0);
				glVertex2f( 0, 0);
				glTexCoord2f(1,0);
				glVertex2f(800,  0);
				glTexCoord2f(1,1);
				glVertex2f( 800, 600);
				glTexCoord2f(0,1);
				glVertex2f( 0,  600);


				glEnd();
				SDL_GL_SwapBuffers();
			}

			else if (player->getFuel() < 150)
			{
				if (Input::isKeyPressed(KEY_SPACE))
				{
					state = playing;
					playSound(waveSound);
					wolfs.clear();
					trees.clear();
					setup();
					player->setHealth(3);
					player->setFuel(0);
					totalTime = 0;
					
				}

				glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texNofuel);
				glBegin(GL_QUADS);

				glTexCoord2f(0,0);
				glVertex2f( 0, 0);
				glTexCoord2f(1,0);
				glVertex2f(800,  0);
				glTexCoord2f(1,1);
				glVertex2f( 800, 600);
				glTexCoord2f(0,1);
				glVertex2f( 0,  600);


				glEnd();
				SDL_GL_SwapBuffers();
			}
			else 
			{
				if (Input::isKeyPressed(KEY_SPACE))
				{
					state = playing;
					playSound(waveSound);
					wolfs.clear();
					trees.clear();
					setup();
					player->setHealth(3);
					player->setFuel(0);
					totalTime = 0;
					
				}

				glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texWin);
				glBegin(GL_QUADS);

				glTexCoord2f(0,0);
				glVertex2f( 0, 0);
				glTexCoord2f(1,0);
				glVertex2f(800,  0);
				glTexCoord2f(1,1);
				glVertex2f( 800, 600);
				glTexCoord2f(0,1);
				glVertex2f( 0,  600);


				glEnd();
				SDL_GL_SwapBuffers();
			}
		}
	}

	SDL_Quit();

	return 0;
}

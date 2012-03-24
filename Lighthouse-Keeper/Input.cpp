#include "Input.h"

Input* Input::instance = NULL;

Input::Input(void)
{
	this->instance = this;
}

Input::~Input(void)
{
}

void Input::init()
{
	instance->exit = false;

	for (int i = 0; i < MAX_KEYS; i++)
	{
		instance->keys[i] = false;
		instance->previousKeys[i] = false;
	}
	
	instance->mousex = 0;
	instance->mousey = 0;
	instance->mouseButton = false;
	instance->previousMouseButton = false;
}

void Input::update()
{
	instance->exit = false;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit = true;
		else 
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_UP)
				{
					instance->keys[KEY_UP] = true;
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					instance->keys[KEY_LEFT] = true;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					instance->keys[KEY_DOWN] = true;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					instance->keys[KEY_RIGHT] = true;
				}
				else if (event.key.keysym.sym == SDLK_SPACE)
				{
					instance->keys[KEY_SPACE] = true;
				}
				else if (event.key.keysym.sym == SDLK_a)
				{
					instance->keys[KEY_A] = true;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					instance->keys[KEY_S] = true;
				}

			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_UP)
				{
					instance->keys[KEY_UP] = false;
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					instance->keys[KEY_LEFT] = false;
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					instance->keys[KEY_DOWN] = false;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					instance->keys[KEY_RIGHT] = false;
				}
				else if (event.key.keysym.sym == SDLK_SPACE)
				{
					instance->keys[KEY_SPACE] = false;
				}
				else if (event.key.keysym.sym == SDLK_a)
				{
					instance->keys[KEY_A] = false;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					instance->keys[KEY_S] = false;
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				instance->mousex = event.button.x;
				instance->mousey = event.button.y;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					mouseButton = true;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					mouseButton = false;
				}
			}
		}
	}
}

bool Input::checkQuit()
{
	return instance->exit;
}

bool Input::isKeyPressed(KEY k)
{
	return instance->keys[k] && !instance->previousKeys[k];
}

float Input::getMouseX()
{
	return instance->mousex;
}

float Input::getMouseY()
{
	return instance->mousey;
}

bool Input::isMousePressed()
{
	return instance->mouseButton && !instance->previousMouseButton;
}
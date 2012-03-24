#pragma once
#include "SDL.h" 

#define MAX_KEYS 7

typedef enum KEY {
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_A,
	KEY_S,
};

class Input
{
public:
	Input(void);
	~Input(void);

	void init();
	void update();
	bool checkQuit();
	static bool isKeyPressed(KEY k);
	static float getMouseX();
	static float getMouseY();
	static bool isMousePressed();

private:
	static Input* instance;

	bool exit;
	bool keys[MAX_KEYS];
	bool previousKeys[MAX_KEYS];
	float mousex;
	float mousey;
	bool mouseButton;
	bool previousMouseButton;
};

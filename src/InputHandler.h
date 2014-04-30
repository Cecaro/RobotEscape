#include "SDL2/SDL.h"

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

class InputHandler {
public: 
	InputHandler();
	~InputHandler();
	void update();
	void clean();

	bool KDown(SDL_Scancode key);
private:
	const Uint8* keystates;
	void onKDown();
	void onKUp();
};
#endif // INPUTHANDLER_H_
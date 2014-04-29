#include "InputHandler.h"

bool InputHandler:: KDown(SDL_Scancode key) {
	if (keystates != 0){
		if (keystates[key] == 1){
			return true;
		}
		else {return false;}

	}
	return false;
}
void InputHandler::update(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				onKDown();
				break;
			case SDL_KEYUP:
				onKUp();
				break;	
		}
	}
}

void InputHandler::onKDown() {
	keystates = SDL_GetKeyboardState(0);
}
void InputHandler::onKUp () {
	keystates = SDL_GetKeyboardState(0);
}

#include "SDL2/SDL.h"

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

class InputHandler {
public:
		static InputHandler* Instance()	{
			if (iInstance == 0) {
				iInstance = new InputHandler();
			}
			return iInstance;
		}
	InputHandler();
	~InputHandler();
	void update();
	void clean(); 
	void reset(); 

	bool KDown(SDL_Scancode key);

private: 
	const Uint8* m_keystates;
	void onKDown();
	void onKUp();
	static InputHandler* iInstance;
};

#endif //GAMEASSET_H_ 
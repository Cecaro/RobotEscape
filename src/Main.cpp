#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "vectormath_cpp/vectormath_aos.h"
#include "GameAsset.h"
#include "Camera.h"
#include "CubeAsset.h"
#include "Player.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

vector<shared_ptr<GameAsset> > assets;
vector<shared_ptr<CubeAsset> >wall;
shared_ptr<Player> player;

SDL_Window * window = nullptr;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL 
 * context was created.
 */
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // This O(n + n^2 + n) sequence of loops is written for clarity,
  // not efficiency
  player->update();
  if (player->assetAlive()){
  	Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(0.0, 0.0, -0.05)));
  }

  for(auto i : assets) {
    for(auto j : assets) {
      if((i != j) && i->collidesWith(*j)) {
	cout << "We have a collision"  << endl;
      }
    }
  }

  for(auto it : assets) {
    it->draw();
  }
  for(auto it: wall){
  	it->draw();
  }
  player->draw();
  
  // Don't forget to swap the buffers
  SDL_GL_SwapWindow(window);
}

int main(int argc, char ** argv) {
	Uint32 width = 640;
	Uint32 height = 480;
	Uint32 delay = 1000/60; // in milliseconds

	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	window = SDL_CreateWindow("Robot Escape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (nullptr == window) {
			cout << "Failed to create SDL window: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (nullptr == glContext) {
			cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
			SDL_Quit();

	}

	// Initialise GLEW - an easy way to ensure OpenGl 2.0+
	// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0")) {
	  cerr<< "OpenGL 2.0 not available" << endl;
	  return 1;
	}

	//load the objects
	//Loading the player
	player = shared_ptr<Player> (new Player(0, 0, 0));
	//Loading the obstacles - formed of 8 cubes put together to have a hole in the middle which the player can go through
	
	//one obstacle creation
	for (int Ox = -1.5; Ox <= 1.5; Ox++){
    	wall.push_back(shared_ptr<CubeAsset> (new CubeAsset(Ox, -1.5, 15)));
    	wall.push_back(shared_ptr<CubeAsset> (new CubeAsset(Ox, 1.5, 15)));
  	}
  	for (int Oy = -1.5; Oy <= 1.5; Oy++){
    	wall.push_back(shared_ptr<CubeAsset> (new CubeAsset(-1.5, Oy, 15)));
    	wall.push_back(shared_ptr<CubeAsset> (new CubeAsset(1.5, Oy, 15)));
  	}	
	//assets.push_back(shared_ptr<CubeAsset> (new CubeAsset(0, 0, 20)));
	// Set the camera
	//Camera::getInstance().lookAt(Point3(0.0, 0.0, -10.0), Point3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0));
	Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(0.0, -2.0, 5.0)));
		display();
	//Camera::getInstance().setCamera(Matrix4::identity());

	// Call the function "display" every delay milliseconds
	//SDL_AddTimer(delay, display, NULL);

	// Add the main event loop
	SDL_Event event;
	bool running = true;
	while (running){
		while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					running = false;
			  		SDL_Quit();
			  		break;
				case SDL_USEREVENT:
			  		display();
			  		break;
				case SDL_KEYUP:
			  	// Camera::getInstance().setCamera(Matrix4::identity());
			  		break;
				case SDL_KEYDOWN:
			  		Matrix4 camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){
			  	case SDLK_LEFT:
			   		Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.5, 0.0, 0.0)) );
			    	player->MoveLeft();
			    	break;
			  	case SDLK_RIGHT:
			    	Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(-0.5, 0.0, 0.0)) );
			    	player->MoveRight();
			    	break;
			  	case SDLK_UP:
			   		Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, -0.5, 0.0)) );
			    	player->MoveUp();
			    	break;
			  	case SDLK_DOWN:
			    	Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.5, 0.0)) );
			    	player->MoveDown();
			    	break;
			  	case SDLK_ESCAPE:
			    	running = false;
			    	break;
			  	default:
			    	break;
			  }
			  break;
			}
		}
		SDL_Delay(10);
		display();
  	}
}
#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <time.h>

#include "vectormath_cpp/vectormath_aos.h"
#include "GameAsset.h"
#include "Camera.h"
#include "CubeAsset.h"
#include "Player.h"
#include "Obstacle.h"
#include "Obstacle2.h"
#include "Floor.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

shared_ptr<Floor> ground;
vector<shared_ptr<Obstacle> >bRect;
vector<shared_ptr<Obstacle2> >sRect;
shared_ptr<Player> player;
SDL_Window * window = nullptr;
int gate1 = 1;
int gate2 = 1;
int gate3 = 1;
int gate4 = 1;

clock_t t;
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
  player->update();
  			//getting the player's coordinates for obstacle spawning
  	 	  	int xp_pos  = int(player->bbox->getCentre()->getX());
  			int yp_pos = int(player->bbox->getCentre()->getY());
  			int zp_pos = int(player->bbox->getCentre()->getZ());
  t = clock();
  double time = ((float)t/CLOCKS_PER_SEC) * 1.5 ;

//Draw the obstacles only if the player is alive; they consitst of 4 blocks: two big rectangles at the top and bottom
//and two thinner ones in the middle, with space in between them
 	 if(player->assetAlive()){
  			int random = rand() % 20;
  		if(fmod(time, 0.3) < 0.04 && gate1 == 1){
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random), 50)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random-26.25), (yp_pos+random+27.5), 50)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random+26.25), (yp_pos+random+27.5), 50)));
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random+55), 50)));
     		gate1 --;
     	}
		if(zp_pos >= 60 && gate2 == 1){
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random), 90)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random-26.25), (yp_pos+random+27.5), 90)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random+26.25), (yp_pos+random+27.5), 90)));
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random+55), 90)));
     		gate2 --;
     	}
     	if(zp_pos >= 110 && gate3 == 1){
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random), 130)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random-26.25), (yp_pos+random+27.5), 130)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random+26.25), (yp_pos+random+27.5), 130)));
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random+55), 130)));
     		gate3 --;
     	}
     	if(zp_pos >= 160 && gate4 == 1){
     		bRect.clear();
     		sRect.clear();
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random), 175)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random-26.25), (yp_pos+random+27.5), 175)));
  			sRect.push_back(shared_ptr<Obstacle2>(new Obstacle2((xp_pos+random+26.25), (yp_pos+random+27.5), 175)));
  			bRect.push_back(shared_ptr<Obstacle>(new Obstacle((xp_pos+random), (yp_pos+random+55), 175)));
     		gate4 --;
     	}
	} 

	//Making the camera follow the player's movement. Stopping it after going through all the obstacles to show that
	//the game has been won
  if (player->assetAlive() && zp_pos<=240){
  	Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(0.0, 0.0, -0.1)));
  }
  	//end the game, win situation
  if(zp_pos >= 300){
  	player->isDead();
  	cout<<"Congratulations, you have escaped the prison! However, your adventure is only starting!"<<endl;
  }

  for(auto i : bRect) {
      if(player->collidesWith(*i)) {
		player->isDead();
		cout<<"Unfortunately, a forcefield nullifier is not equiped! Trying to go through one means death for you."<<endl;
		cout<"Please come back after training fast reflexes."<<endl;
      }

  }
  for (auto i : sRect) {
  	if (player->collidesWith(*i)) {
  		player->isDead();
  		cout<<"Unfortunately, a forcefield nullifier is not equiped! Trying to go through one means death for you."<<endl;
  		cout<"Please come back after training fast reflexes."<<endl;
  	}
  }

  ground->draw();
  for(auto it: bRect){
  	it->draw();
  }
  for (auto it:sRect){
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

	//Depth Buffer Setup - necessity for 3D collision
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);


	//load the objects
	ground = shared_ptr<Floor> (new Floor(0,0,0));
	//Loading the player
	player = shared_ptr<Player> (new Player(0, 0, 0));

	// Set the camera
	Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(0.0, -1.0, 10.0)));
		display();

	// Add the main event loop
	SDL_Event event;
	bool running = true;
	while (running){
		  if(player->isItAlive() == false){
  			SDL_Quit();
  			running = false;
 		  }
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
					//onKUp();
			  		break;
				case SDL_KEYDOWN:
					//onKDown();
			  		Matrix4 camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){
			  	case SDLK_LEFT:
			   		Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(1.0, 0.0, 0.0)) );
			    	player->MoveLeft();
			    	break;
			  	case SDLK_RIGHT:
			    	Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(-1.0, 0.0, 0.0)) );
			    	player->MoveRight();
			    	break;
			  	case SDLK_UP:
			   		Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, -1.0, 0.0)) );
			    	player->MoveUp();
			    	break;
			  	case SDLK_DOWN:
			  	//The condition prevents the player from going through the ground
			  	if(player->bbox->getCentre()->getY() >= -28){
			    	Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 1.0, 0.0)) );
			    	player->MoveDown();
			    }
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
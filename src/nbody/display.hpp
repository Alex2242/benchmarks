#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



#ifndef DISPLAY
#define DISPLAY


class Display {
	protected:
		SDL_Window *window;
		SDL_GLContext glContext;
		SDL_Event events;
		bool finished;


	public:
		Display();
		~Display();
		void step();
		bool drawBodies(int N, double *x, double *y);

};

#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "glcamera.hpp"
#include "nbody.hpp"

#ifndef DISPLAY
#define DISPLAY


class Display {
	protected:
		SDL_Window *window;
		SDL_GLContext glContext;
		SDL_Event events;
		GlCamera *cam;


	public:
		Display();
		~Display();
		bool drawBodies2D(bodiesPosition *positions);
		bool drawBodies3D(bodiesPosition *positions);

};

#endif

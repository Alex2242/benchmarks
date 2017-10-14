#include "display.hpp"



Display::Display() {
	window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);
 	glPointSize(5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	finished = 0;}

Display::~Display() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit(); }



void Display::step() {
	while (SDL_PollEvent(&events)) {
		    if(events.window.event == SDL_WINDOWEVENT_CLOSE)
			    finished = true; }

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	//drawPoints(t/1000);
	usleep(700);
	SDL_GL_SwapWindow(window);
}

bool Display::drawBodies(int N, double *x, double *y) {
  while (SDL_PollEvent(&events)) {
		    if(events.window.event == SDL_WINDOWEVENT_CLOSE)
			    return 0; }

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glBegin(GL_POINTS);
		for (int i = 0; i < N; i++ )
			glVertex2d(x[i],y[i]);
	glEnd();
	glFlush();
	SDL_GL_SwapWindow(window);

	return 1;
}

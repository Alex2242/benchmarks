#include "display.hpp"



Display::Display() {
	window = SDL_CreateWindow("Nbody Simulation", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	glContext = SDL_GL_CreateContext(window);
	glPointSize(5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective(70, (double) 800/600, 0.001, 1000);

	cam = new GlCamera(1.0, 1.0, 1.0);
 }

Display::~Display() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



bool Display::drawBodies2D(bodiesPosition *positions) {
	while (SDL_PollEvent(&events)) {
		if(events.wheel.y == 1)
			cam->changeDist(0.1);
		if(events.wheel.y == -1)
			cam->changeDist(-0.1);
		if(events.window.event == SDL_WINDOWEVENT_CLOSE)
			return 0;
	}

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	cam->look();

	glBegin(GL_POINTS);
		for (int i = 0; i < positions->N; i++ ){
			glColor3ub(255,255,255);
			glVertex2d(positions->x[i],positions->y[i]);
		}
	glEnd();

	delete positions;

	glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex2f(0.0 , 0.0);
		glColor3ub(255, 0, 0);
		glVertex2f(1.0 , 0.0);

		glColor3ub(0, 255, 0);
		glVertex2f(0.0 , 0.0);
		glColor3ub(0, 255, 0);
		glVertex2f(0.0 , 1.0);
	glEnd();

	glFlush();
	SDL_GL_SwapWindow(window);

	return 1;
}


/*
bool Display::drawBodies3D() {
	while (SDL_PollEvent(&events)) {
		if(events.wheel.y == 1)
			cam->changeDist(0.1);
		if(events.wheel.y == -1)
			cam->changeDist(-0.1);
	    if(events.window.event == SDL_WINDOWEVENT_CLOSE)
		    return 0; }

	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	cam->look();

	glBegin(GL_POINTS);
		for (int i = 0; i < N; i++ ){
			glColor3ub(255,255,255);
			glVertex3d(x[i],y[i],z[i]);}
	glEnd();

	glBegin(GL_LINES);
		glColor3ub(0,0,255);
		glVertex3f(0.0 , 0.0 , 0.0);
		glColor3ub(0,0,255);
		glVertex3f(1.0 , 0.0 , 0.0);

		glColor3ub(0,255,0);
		glVertex3f(0.0 , 0.0 , 0.0);
		glColor3ub(0,255,0);
		glVertex3f(0.0 , 1.0 , 0.0);

		glColor3ub(255,0,0);
		glVertex3f(0.0 , 0.0 , 0.0);
		glColor3ub(255,0,0);
		glVertex3f(0.0 , 0.0 , 1.0);
	glEnd();

	glFlush();
	SDL_GL_SwapWindow(window);

	return 1;
}
*/



bool Display::drawBodies3D(bodiesPosition *positions){
	while (SDL_PollEvent(&events)) {
		if(events.wheel.y == 1)
			cam->changeDist(0.1);
		if(events.wheel.y == -1)
			cam->changeDist(-0.1);
		if(events.window.event == SDL_WINDOWEVENT_CLOSE)
			return 0;
	}

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	cam->look();

	glBegin(GL_POINTS);
		for (int i = 0; i < positions->N; i++ ){
			glColor3ub(255,255,255);
			glVertex3d(positions->x[i],positions->y[i],positions->z[i]);
		}
	glEnd();

	delete positions;

	glBegin(GL_LINES);
		glColor3ub(0,0,255);
		glVertex3f(0.0 , 0.0 , 0.0);
		glColor3ub(0,0,255);
		glVertex3f(1.0 , 0.0 , 0.0);

		glColor3ub(0,255,0);
		glVertex3f(0.0 , 0.0 , 0.0);
		glColor3ub(0,255,0);
		glVertex3f(0.0 , 1.0 , 0.0);

		glColor3ub(255,0,0);
		glVertex3f(0.0 , 0.0 , 0.0);
		glColor3ub(255,0,0);
		glVertex3f(0.0 , 0.0 , 1.0);
	glEnd();

	glFlush();
	SDL_GL_SwapWindow(window);

	return 1;
}

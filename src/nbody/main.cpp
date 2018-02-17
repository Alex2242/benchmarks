#include <iostream>

#include "display.hpp"
#include "nbody.hpp"



int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Usage : <Number of bodies> <dt> \n" ;
		return 0;
	}

	float dt ;
	sscanf(argv[2],"%f",&dt);
    int N = std::stoi(argv[1]);
    bool res = 1;

  	Nbody *nbody = new Nbody(N,dt);
    Display *disp = new Display();

    while (res) {
		nbody->compute3D();
		res = disp->drawBodies3D(nbody->getPositions());
	}

  	return 0;
}


/*
void drawPoints(float *x, float *y) {
    glBegin(GL_POINTS);
            glVertex2f(x[0],y[0]);
            glVertex2f(x[1],y[1]);
            glVertex2f(x[2],y[2]);
    glEnd();
    glFlush();
}


/*
int azemain(int argc, char **argv) {
    // Notre fenêtre
    SDL_Window* window(0);
    SDL_GLContext glContext(0);
    SDL_Event events;
    bool finished(false);

    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " <<
            SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Version d'OpenGL
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Création de la fenêtre
    window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == 0) {
        std::cout << "Erreur lors de la creation de la window : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Création du contexte OpenGL
    glContext = SDL_GL_CreateContext(window);

    if(glContext == 0) {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};
    glPointSize(5);

    float t = 0;

    // Boucle principale
    while(!finished) {
        while (SDL_PollEvent(&events)) {
                if(events.window.event == SDL_WINDOWEVENT_CLOSE)
                    finished = true; }

        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0, 1.0, 1.0);
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

        //drawPoints(t/1000);

        usleep(700);
        SDL_GL_SwapWindow(window);
        t++;

    }

    // On quitte la SDL
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}

*/

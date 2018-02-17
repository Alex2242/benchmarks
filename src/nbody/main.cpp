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

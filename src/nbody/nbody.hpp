#include <iostream>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <random>


#ifndef NBODY
#define  NBODY



class Nbody {
	protected:
		int NBodies;
		float dt,G;
		double *x, *y,*vx,*vy, **positions;
		int m; // assumes that mass is uniform on all bodies


	public:
		Nbody(int n, float dt =10.0, int mass=1);
		~Nbody();
		double norm(double x,double y);
		double theta(double x1,double x2,double y1,double y2) ;
		double ** compute();

};

#endif

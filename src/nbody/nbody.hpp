#include <iostream>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <random>
#include <GL/gl.h>


#ifndef NBODY
#define NBODY

typedef struct bodiesPosition_ {
	int N;
	double *x;
	double *y;
	double *z;
} bodiesPosition;


class Nbody {
	protected:
		int nBodies;
		float dt,G;
		double *x, *y, *z, *vx, *vy, *vz, **positions;
		int m; // assumes that mass is uniform on all bodies


	public:
		Nbody(int n, float dt =10.0, int mass=1);
		~Nbody();
		double norm(double x,double y);
		double theta(double x1,double x2,double y1,double y2) ;
		void compute2D();
		void compute3D();
		bodiesPosition * getPositions();

};

#endif

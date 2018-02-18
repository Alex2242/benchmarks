#include "nbody.hpp"


Nbody::Nbody(int n, float dt, int mass ) {
	nBodies = n;
	m = mass;
	G = 6.67 * pow(10,-11);
	this->dt = dt;
	x = new double[n];
	y = new double[n];
	z = new double[n];
	vx = new double[n];
	vy = new double[n];
	vz = new double[n];

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(-1, 1);

	for (int i = 0; i < n; i++) {
		x[i] = dist(mt);
		y[i] = dist(mt);
		z[i] = dist(mt);
		vx[i] = 0.0 ;
		vy[i] = 0.0 ;
		vz[i] = 0.0 ;
	}

	positions = new double*[3];
	positions[0] = x;
	positions[1] = y;
	positions[2] = z;
}

Nbody::~Nbody() {
	delete x,y,positions,vx,vy;
}

double Nbody::norm(double x,double y) {
	return sqrt( pow(x,2) + pow(y,2));
}

double Nbody::theta(double x1,double x2,double y1,double y2) {
    return (atan( (y2-y1) / (x2-x1) ) );
}

void Nbody::compute2D() {
	double fx,fy;
	for (int tB = 0; tB < nBodies; tB++) { // tB = thisBody
		fx = 0; fy = 0;
		for (int oB = 0; oB < nBodies; oB++){ // oB = otherBody
			if (oB != tB){
				fx += G * pow(m,2) * (x[oB] - x[tB]) / (pow(abs(x[oB] - x[tB]), 2) + 0.01 );
				fy += G * pow(m,2) * (y[oB] - y[tB]) / (pow(abs(y[oB] - y[tB]), 2) + 0.01 );
			}
		}

		vx[tB] += fx * dt / m;
		x[tB]  += vx[tB] * dt;

		vy[tB] += fy * dt / m;
		y[tB]  += vy[tB] * dt;
	}
}


void Nbody::compute3D() {
	double fx,fy,fz;
	for (int tB = 0; tB < nBodies; tB++) { // tB = thisBody
		fx = 0; fy = 0; fz = 0;
		for (int oB = 0; oB < nBodies; oB++){ // oB = otherBody
			if (oB != tB){
				fx += G * pow(m,2) * (x[oB] - x[tB]) / (pow(abs(x[oB] - x[tB]), 3) + 0.01 );
				fy += G * pow(m,2) * (y[oB] - y[tB]) / (pow(abs(y[oB] - y[tB]), 3) + 0.01 );
				fz += G * pow(m,2) * (z[oB] - z[tB]) / (pow(abs(z[oB] - z[tB]), 3) + 0.01 );
			}
		}

		vx[tB] += fx * dt / m;
		x[tB]  += vx[tB] * dt;

		vy[tB] += fy * dt / m;
		y[tB]  += vy[tB] * dt;

		vz[tB] += fz * dt / m;
		z[tB]  += vz[tB] * dt;
	}
}

bodiesPosition * Nbody::getPositions(){
	bodiesPosition *positions = new bodiesPosition;
	positions->x = new double[nBodies];
	positions->y = new double[nBodies];
	positions->z = new double[nBodies];

	for (int i = 0; i < nBodies; i++) {
		positions->x[i] = x[i];
		positions->y[i] = y[i];
		positions->z[i] = z[i];
	}
	positions->N = nBodies;

	return positions;
}

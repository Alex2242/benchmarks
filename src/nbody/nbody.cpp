#include "nbody.hpp"



Nbody::Nbody(int n, float dt, int mass ) {
	NBodies = n;
	m = mass;
	G = 6.67 * pow(10,-11);
	this->dt = dt;
	x = new double[n];
	y = new double[n];
	vx = new double[n];
	vy = new double[n];

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(-1, 1);

	for (int i = 0; i < n; i++) {
		x[i] = dist(mt);
		y[i] = dist(mt);
		vx[i] = 0.0 ;
		vy[i] = 0.0 ; }

	positions = new double*[2];
	positions[0] = x;
	positions[1] = y;


}

Nbody::~Nbody() {
	delete x,y,positions,vx,vy;
}

double Nbody::norm(double x,double y) {
	return sqrt( pow(x,2) + pow(y,2)); }

double Nbody::theta(double x1,double x2,double y1,double y2) {
    return ( atan( (y2-y1) / (x2-x1) ) ); }

double ** Nbody::compute() {
	double fx,fy;
	for (int tB = 0; tB < NBodies; tB++) { // tB = thisBody
	    fx = 0;fy = 0;
	    for (int oB = 0; oB < NBodies; oB++){ // oB = otherBody
	      if (oB != tB){
	     	fx += G * pow(m,2) * (x[oB] - x[tB]) / (pow( abs(x[oB] - x[tB]), 3) + 0.01 );
	    	fy += G * pow(m,2) * (y[oB] - y[tB]) / (pow( abs(y[oB] - y[tB]), 3) + 0.01 ); }
		}

	    vx[tB] += fx * dt / m;
	    x[tB] += vx[tB] * dt;

	    vy[tB] += fy * dt / m;
	    y[tB] += vy[tB] * dt;


	}
	/*
	std::cout << "x : " << x[NBodies-1] << "   y : " << y[NBodies-1] << '\n';
	std::cout << "vx : " << vx[NBodies-1] << "   vy : " << vy[NBodies-1] << '\n';
	std::cout << "fx : " << fx << "   fy : " << fy << '\n';
	std::cout << "\n\n\n";*/
	return positions;
}

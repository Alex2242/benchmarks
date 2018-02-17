#include "glcamera.hpp"


GlCamera::GlCamera(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
	r = sqrt( pow(x,2) + pow(y,2) + pow(z,2) );
	theta = acos(z / r);
	phi = atan(y / x);
	std::cout << "distance " << r << "  theta  " << theta << "  phi  "
		<<  phi  << "  x  " << x <<
	 	"  y  " << y << "  z  " << z  << std::endl;
	look();
}

GlCamera::~GlCamera(){}

void GlCamera::changeDist(float delta) {
	r += delta;
	x = r * cos(phi) * sin(theta);
	y = r * sin(phi) * sin(theta);
	z = r * cos(theta);
	std::cout << "distance " << r << "  theta  " << theta << "  phi  "
		<<  phi  << "  x  " << x <<
	 	"  y  " << y << "  z  " << z  << std::endl;
}

void GlCamera::look() {
	gluLookAt(x,y,z,0,0,0,0,0,1);
}

void GlCamera::lookAt(float cx,float cy, float cz) {
	gluLookAt(cx,cy,cz,0,0,0,0,0,1);
}

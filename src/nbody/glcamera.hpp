#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#ifndef GLCAMERA
#define GLCAMERA


class GlCamera {
	protected:
		float x, y, z, phi, theta, r; // using Spherical coordinate system

	public:
		GlCamera(float x, float y, float z);
		~GlCamera();
		void changeDist(float delta);
		void look();
		void lookAt(float cx,float cy, float cz);

};


#endif

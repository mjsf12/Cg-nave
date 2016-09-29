/*
 * Meteoro.cpp
 *
 *  Created on: 12/09/2016
 *      Author: lcc
 */

#include "Meteoro.h"
void Meteoro::initRandomSeed() {
	static bool initialized = false;
	if (!initialized) {
		srand(int(time(NULL)));
		initialized = true;
	}
}
void Meteoro::setRandomSeed(int seed) {
	this->initRandomSeed();
	srand(seed);
}

int Meteoro::randomReal(double low, double high) {
	this->initRandomSeed();
		double d = rand() / (double(RAND_MAX) + 1);
		double s = d * (double(high) - low + 1);
	return (int)(floor(low + s));
}
Meteoro::Meteoro() {
	collisor = false;
	// TODO Auto-generated constructor stub
	this->xWalk = 0;
	this->yWalk = 0;
	this->zWalk = 0;
	x = this->randomReal(range,-range);
	y = this->randomReal(-range, range);
	z = this->randomReal(range,-range);
	int side = (int)(this->randomReal(0,7));

	switch(side){
		case 1:
			xWalk =-10;
			break;
		case 2:
			xWalk = 10;
			break;
		case 3:
			yWalk =-10;
			break;
		case 4:
			yWalk = 10;
			break;
		case 5:
			zWalk =-10;
			break;
		case 6:
			zWalk = 10;
			break;
	}
	//usleep(100);
}

void Meteoro::drawCube(float move){
	x += xWalk;
	y += yWalk;
	z += zWalk;
	
	glPushMatrix();
		glTranslatef(x,y,z);
		glutSolidSphere(2,5,5);
	glPopMatrix();
    if (x > range + 1 or x < -range + 1){
		xWalk*=-1;
	}
	if (z > range + 1 or z < -range + 1){
		zWalk*=-1;
	}
    if (y > range + 1 or y < -range + 1){
		yWalk*=-1;
	}
}

Meteoro::~Meteoro() {
	// TODO Auto-generated destructor stub
}

void Meteoro::setTranslate(float _x, float _y, float _z){
	x += _x;
	y += _y;
	z += _z;
}

float Meteoro::getX(){
	return x;
}

float Meteoro::getY(){
	return y;
}

float Meteoro::getZ(){
	return z;
}

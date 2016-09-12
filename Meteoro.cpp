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
	// TODO Auto-generated constructor stub

	x = this->randomReal(1,100);
	y = this->randomReal(1,100);
	z = this->randomReal(-30,-1);
}

void Meteoro::drawCube(){
	glPushMatrix();
		glTranslatef(x,y,z);
		glutSolidCube(2);
	glPopMatrix();
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

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
	coletable = false;
	// TODO Auto-generated constructor stub
	this->xWalk = 0;
	this->yWalk = 0;
	this->zWalk = 0;
	x = this->randomReal(30,-30);
	y = this->randomReal(-30, 30);
	z = this->randomReal(-100,-range);
	if(randomReal(0,100) > 80)
		coletable = true;

	zWalk = 5;
	xWalk = 1;
	yWalk = 1;
}

void Meteoro::drawCube(float move){
	z += zWalk;
	xWalk++;
	
	glPushMatrix();
		glTranslatef(x,y,z);
		glutSolidSphere(2,5,5);
	glPopMatrix();
	Reset();
}

void Meteoro:: Reset(){
	if(z  > 30){
		x = this->randomReal(30,-30);
		y = this->randomReal(-30, 30);
		z = this->randomReal(-100,-range);
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

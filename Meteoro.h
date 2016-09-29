/*
 * Meteoro.h
 *
 *  Created on: 12/09/2016
 *      Author: lcc
 */

#ifndef METEORO_H_
#define METEORO_H_

#include <cstdlib>
#include <ctime>
#include <GL/freeglut.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
using namespace std;

class Meteoro {
public:
	int range = 300;
	float x,y,z,xWalk,yWalk,zWalk;
	void initRandomSeed();
	void setRandomSeed(int);
	int randomReal(double,double);
	bool collisor;
	Meteoro();
	void setTranslate(float,float,float);
	void drawCube(float);
	float getX();
	float getY();
	float getZ();
	virtual ~Meteoro();
};

#endif /* METEORO_H_ */

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

class Meteoro {
private:
	float x,y,z;
	void initRandomSeed();
	void setRandomSeed(int);
	int randomReal(double,double);
public:
	Meteoro();
	void setTranslate(float,float,float);
	void drawCube();
	float getX();
	float getY();
	float getZ();
	virtual ~Meteoro();
};

#endif /* METEORO_H_ */

/*
 * KinematicChain.h
 *
 *  Created on: Nov 5, 2012
 *      Author: malcom
 */

#ifndef KINEMATICCHAIN_H_
#define KINEMATICCHAIN_H_
#include "bullet/LinearMath/btQuaternion.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btTransform.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define angolo1 0
#define angolo2 1
#define angolo3 2
#define global1 3
#define global2 4
#define global3 5

class KinematicChain {
public:

	KinematicChain(float x,float y, float z);
	void Draw();
	void update();
	virtual ~KinematicChain();

	int x,y,z;
	int offset1,offset2,offset3;
	btVector3 Points[4];
	btVector3 basePoints[4];
	btVector3 centerOfMass;
	float parametri[3];

};

#endif /* KINEMATICCHAIN_H_ */

/*
 * Finger.h
 *
 *  Created on: Nov 8, 2012
 *      Author: malcom
 */

#ifndef FINGER_H_
#define FINGER_H_

#include "bullet/LinearMath/btQuaternion.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btTransform.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define TORAD 3.14/180

class Finger {
public:
	Finger(float x,float y, float z, btVector3 com);
	virtual ~Finger();
	void update();
	void draw();
	void rotate(float angle);

	float x,y,z;
	float angle1,angle2,angle3;
	float offset1;
	float offset2;
	float offset3;
	float globalAngle;

	btVector3 Points[4];
	btVector3 basePoints[4];
	btVector3 centerOfMass;
};

#endif /* FINGER_H_ */

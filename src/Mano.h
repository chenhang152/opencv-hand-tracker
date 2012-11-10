/*
 * Mano.h
 *
 *  Created on: Nov 9, 2012
 *      Author: malcom
 */

#ifndef MANO_H_
#define MANO_H_

#include "bullet/LinearMath/btQuaternion.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btTransform.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Finger.h"

class Mano {
public:
	Mano(btVector3 com);
	virtual ~Mano();

	Finger * dita[5];

	float test;

	void Draw();
	void Rotate();
	btVector3 centerOfMass;
};

#endif /* MANO_H_ */

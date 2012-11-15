/*
 * Aggregato.h
 *
 *  Created on: Nov 12, 2012
 *      Author: malcom
 */

#ifndef AGGREGATO_H_
#define AGGREGATO_H_

#include "bullet/LinearMath/btQuaternion.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btTransform.h"
#include "KinematicChain.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Aggregato {
public:
	Aggregato();
	void Draw();
	void update();

	KinematicChain * dita[5];
	float * parametri[15];

	virtual ~Aggregato();
};

#endif /* AGGREGATO_H_ */

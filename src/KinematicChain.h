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
	KinematicChain(int id=0);
	void Draw();
	void update();
	void A1();
	void A2();
	void A3();
	void GlobRotate();
	virtual ~KinematicChain();

	int x,y,z;
	float parametri[6];
	int offset;
	int id;

	//rappresentano le posizioni dei punti nello spazio
	//IN PARTICOLARE:
	//devo valutare la funzione di errore sull'ultimo punto, ovvero il finger tip.
	//IL PSO:
	//deve modificare i valori su angle1-2-3 e su global1-2-3

	btVector3 Points[4];



};

#endif /* KINEMATICCHAIN_H_ */

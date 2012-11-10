/*
 * Mano.cpp
 *
 *  Created on: Nov 9, 2012
 *      Author: malcom
 */

#include "Mano.h"

Mano::Mano(btVector3 com) {

	centerOfMass=com;
	int off=0;
	test=0;
	for(int i=0;i<5;i++)
	{
	dita[i]=new Finger(0,-100+i*50,0,centerOfMass);
	}


}

Mano::~Mano() {
	// TODO Auto-generated destructor stub
}


void Mano::Draw()
{
	for(int i=0;i<5;i++)
		{
		dita[i]->draw();
		}

	glPushMatrix();
	glBegin(GL_POINTS);
	glPointSize(10.0f);
	glColor3f(0,0,1);
	glVertex3f(centerOfMass.x(),centerOfMass.y(),centerOfMass.z());
	glPointSize(10.0f);
	glColor3f(1,1,1);
	glEnd();
	glPopMatrix();
}

void Mano::Rotate()
{
	test+=1;
	for(int i=0;i<5;i++)
			{
			dita[i]->rotate(test);
			}

}

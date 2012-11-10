/*
 * KinematicChain.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: malcom
 */

#include "KinematicChain.h"


KinematicChain::KinematicChain(int id) {

	this->id=id;
	x=0;y=200;z=0;
	offset=200;
	for (int i =0; i<6;i++)
	{
		parametri[i]=0;
	}

	Points[0]=btVector3(0,100,100);

	btQuaternion q1( parametri[0],0,0);
	btQuaternion q2( parametri[1],0,0);
	btQuaternion q3( parametri[2],0,0);
	btMatrix3x3 r1(q1);
	btMatrix3x3 r2(q2);
	btMatrix3x3 r3(q3);

	//Points[1]=Points[0]+btVector3(offset,0,0);
	Points[1]=Points[0]+r1*btVector3(offset,0,0);
	Points[2]=Points[1]+r1*r2*btVector3(offset,0,0);
	Points[3]=Points[2]+r1*r2*r3*btVector3(offset,0,0);
}

void KinematicChain::Draw() {
	this->update();

	glPointSize(10.0f);

	glBegin(GL_POINTS);
	glColor3f(0,1,0);
	glVertex3f(Points[0].x(),Points[0].y(),Points[0].z());

	glColor3f(1,1,1);
	glVertex3f(Points[1].x(),Points[1].y(),Points[1].z());
	glVertex3f(Points[2].x(),Points[2].y(),Points[2].z());
	glColor3f(1,0,0);
	glVertex3f(Points[3].x(),Points[3].y(),Points[3].z());
	glColor3f(1,1,1);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Points[0].x(),Points[0].y(),Points[0].z());
	glVertex3f(Points[1].x(),Points[1].y(),Points[1].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Points[1].x(),Points[1].y(),Points[1].z());
	glVertex3f(Points[2].x(),Points[2].y(),Points[2].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(Points[2].x(),Points[2].y(),Points[2].z());
	glVertex3f(Points[3].x(),Points[3].y(),Points[3].z());
	glEnd();

}

void  KinematicChain::update() {

	btQuaternion q1( parametri[0],0,0);
	btQuaternion q2( parametri[1],0,0);
	btQuaternion q3( parametri[2],0,0);

	btQuaternion globalR(parametri[3],parametri[4],parametri[5]);

	btMatrix3x3 g(globalR);
	btMatrix3x3 r1(q1);
	btMatrix3x3 r2(q2);
	btMatrix3x3 r3(q3);



	Points[1]=Points[0]+btVector3(offset,0,0);
	Points[1]=r1*Points[1];
	Points[2]=Points[1]+r1*r2*btVector3(offset,0,0);
	Points[3]=Points[2]+r1*r2*r3*btVector3(offset,0,0);


	Points[1]=g*Points[1];
	Points[2]=g*Points[2];
	Points[3]=g*Points[3];


}

KinematicChain::~KinematicChain() {
	// TODO Auto-generated destructor stub
}


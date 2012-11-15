/*
 * Finger.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: malcom
 */

#include "Finger.h"

Finger::Finger(float x,float y, float z, btVector3 com)
{

	this->centerOfMass=com;

	this->x=x;
	this->y=y;
	this->z=z;

	this->globalAngle=0;

	this->angle1=0;
	this->angle2=20;
	this->angle3=0;

	this->offset1=140;
	this->offset2=120;
	this->offset3=100;

	btQuaternion q1( angle1,0,0);
	btQuaternion q2( angle2,0,0);
	btQuaternion q3( angle3,0,0);
	btMatrix3x3 r1(q1);
	btMatrix3x3 r2(q2);
	btMatrix3x3 r3(q3);

	basePoints[0]=centerOfMass+btVector3(x,y,z);
	basePoints[1]=basePoints[0]+r1*btVector3(offset1,0,0);
	basePoints[2]=basePoints[1]+r1*r2*btVector3(offset2,0,0);
	basePoints[3]=basePoints[2]+r1*r2*r3*btVector3(offset3,0,0);

}

Finger::~Finger() {
	// TODO Auto-generated destructor stub
}

void Finger::update()
{

//	basePoints[0]=basePoints[0]+centerOfMass;
//	basePoints[1]=basePoints[1]+centerOfMass;
//	basePoints[2]=basePoints[2]+centerOfMass;
//	basePoints[3]=basePoints[3]+centerOfMass;


	angle3=angle2;

	angle1*=TORAD;
	angle2*=TORAD;
	angle3*=TORAD;


	btQuaternion q1( angle1,0,0);
	btQuaternion q2( angle2,0,0);
	btQuaternion q3( angle3/6*5,0,0);

	btMatrix3x3 r1(q1);
	btMatrix3x3 r2(q2);
	btMatrix3x3 r3(q3);

	float ax=globalAngle;
	float ay=0;
	float az=90;

	btQuaternion globalR(ax*3.14/180,ay*3.14/180,az*3.14/180);
	btMatrix3x3 g(globalR);

	Points[0]=basePoints[0];
	Points[1]=basePoints[0]+r1*btVector3(offset1,0,0);
	Points[2]=basePoints[1]+r1*r2*btVector3(offset2,0,0);
	Points[3]=basePoints[2]+r1*r2*r3*btVector3(offset3,0,0);

	Points[0]=g*(Points[0]-centerOfMass)+centerOfMass;
	Points[1]=g*(Points[1]-centerOfMass)+centerOfMass;
	Points[2]=g*(Points[2]-centerOfMass)+centerOfMass;
	Points[3]=g*(Points[3]-centerOfMass)+centerOfMass;


}


void Finger::rotate(float angle)
{
	globalAngle=angle;
	std::cout <<"global angle "<<globalAngle<<std::endl;

}
void Finger::draw()
{
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

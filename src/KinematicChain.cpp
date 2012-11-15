/*
 * KinematicChain.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: malcom
 */

#include "KinematicChain.h"


KinematicChain::KinematicChain(float x,float y, float z,float mod, int pollice)
{

	this->pollice=pollice;

	this->x=x;
	this->y=y;
	this->z=z;

	cout <<"Istanziato oggetto cinematico"<<endl;
	cout <<x<<" "<<y<<" "<<z<<endl;

	this->mod=mod;

	this->offset1=140*mod;
	this->offset2=120*mod;
	this->offset3=100*mod;

	btVector3 centerOfMass(0,0,0);

	btQuaternion q1( 0,0,0);
	btQuaternion q2( 0,0,0);
	btQuaternion q3( 0,0,0);
	btMatrix3x3 r1(q1);
	btMatrix3x3 r2(q2);
	btMatrix3x3 r3(q3);

	basePoints[0]=btVector3(this->x,this->y,this->z);
	basePoints[1]=basePoints[0]+r1*btVector3(offset1,0,0);
	basePoints[2]=basePoints[1]+r1*r2*btVector3(offset2,0,0);
	basePoints[3]=basePoints[2]+r1*r2*r3*btVector3(offset3,0,0);

	parametri[0]=0;
	parametri[1]=0;

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

	//btQuaternion q1( parametri[2],parametri[0],0);

	const float torand=3.14/180;

	if(parametri[0]<=-90*torand)parametri[0]=-90*torand;
	if(parametri[1]<=-90*torand)parametri[1]=-90*torand;
	if(parametri[0]>=0)parametri[0]=0;
	if(parametri[1]>=0)parametri[1]=0;

	btQuaternion q1;
	if(pollice)
		{
			 q1=btQuaternion( -180*3.14/180,-90*3.14/180,0);
		}
		else
		{
			 q1=btQuaternion( 0,parametri[0],0);
		}

	btQuaternion q2( 0,parametri[1],0);

	if(pollice){q2=btQuaternion( 0,-90*3.14/180,0);}

	btQuaternion q3( 0,parametri[1]*5/6,0);

	btMatrix3x3 r1(q1);
	btMatrix3x3 r2(q2);
	btMatrix3x3 r3(q3);


	Points[0]=basePoints[0];
	Points[1]=Points[0]+r1*btVector3(0,0,offset1);
	Points[2]=Points[1]+r2*r1*btVector3(0,0,offset2);
	Points[3]=Points[2]+r3*r2*r1*btVector3(0,0,offset3);

}

KinematicChain::~KinematicChain() {
	// TODO Auto-generated destructor stub
}


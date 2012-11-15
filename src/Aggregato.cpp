/*
 * Aggregato.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: malcom
 */

#include "Aggregato.h"

Aggregato::Aggregato() {


	int offset=70;

	dita[0]= new KinematicChain(0,0,0,0.6,1);
	dita[1]= new KinematicChain(50,0,0,1);
	dita[2]= new KinematicChain(100,0,0,1.1);
	dita[3]= new KinematicChain(150,0,0,1);
	dita[4]= new KinematicChain(200,0,0,0.8);

	parametri[0]=&(dita[0]->parametri[0]);
	parametri[1]=&(dita[0]->parametri[1]);


	parametri[2]=&(dita[1]->parametri[0]);
	parametri[3]=&(dita[1]->parametri[1]);


	parametri[4]=&(dita[2]->parametri[0]);
	parametri[5]=&(dita[2]->parametri[1]);


	parametri[6]=&(dita[3]->parametri[0]);
	parametri[7]=&(dita[3]->parametri[1]);


	parametri[8]=&(dita[4]->parametri[0]);
	parametri[9]=&(dita[4]->parametri[1]);


}

Aggregato::~Aggregato() {

}


void Aggregato::Draw() {

	dita[0]->Draw();
	dita[1]->Draw();
	dita[2]->Draw();
	dita[3]->Draw();
	dita[4]->Draw();



	glLineWidth(6.0f);
	glBegin(GL_LINES);
	glVertex3f(dita[0]->Points[0].x(),dita[0]->Points[0].y(),dita[0]->Points[0].z());
	glVertex3f(dita[1]->Points[0].x(),dita[1]->Points[0].y(),dita[1]->Points[0].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(dita[1]->Points[0].x(),dita[1]->Points[0].y(),dita[1]->Points[0].z());
	glVertex3f(dita[2]->Points[0].x(),dita[2]->Points[0].y(),dita[2]->Points[0].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(dita[2]->Points[0].x(),dita[2]->Points[0].y(),dita[2]->Points[0].z());
	glVertex3f(dita[3]->Points[0].x(),dita[3]->Points[0].y(),dita[3]->Points[0].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(dita[3]->Points[0].x(),dita[3]->Points[0].y(),dita[3]->Points[0].z());
	glVertex3f(dita[4]->Points[0].x(),dita[4]->Points[0].y(),dita[4]->Points[0].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(dita[4]->Points[0].x(),dita[4]->Points[0].y(),dita[4]->Points[0].z());
	glVertex3f(dita[4]->Points[0].x()-30,dita[4]->Points[0].y()-200,dita[4]->Points[0].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(dita[0]->Points[0].x(),dita[0]->Points[0].y(),dita[0]->Points[0].z());
	glVertex3f(dita[0]->Points[0].x()+30,dita[0]->Points[0].y()-200,dita[0]->Points[0].z());
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(dita[4]->Points[0].x()-30,dita[4]->Points[0].y()-200,dita[4]->Points[0].z());
	glVertex3f(dita[0]->Points[0].x()+30,dita[0]->Points[0].y()-200,dita[0]->Points[0].z());
	glEnd();


	glLineWidth(1.0f);


}

void Aggregato::update() {

	dita[0]->update();
	dita[1]->update();
	dita[2]->update();
	dita[3]->update();
	dita[4]->update();

}
